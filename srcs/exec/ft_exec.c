/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:39:30 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/18 15:29:40 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parse_and_exec(char *line, t_all *a)
{
	int	i;
	int start;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		start = i;
		a->tree = malloc_gc(&a->gc, sizeof(t_tree));
		a->tree->type = -1;
		while (line[i])
		{
			ft_is_quote(line[i], &quote);
			if (line[i] == ';' && !quote &&\
			!ft_is_bs_before(line, i))
				break ;
			i++;
		}
		a->tree->loop = 0;
		a->tree = ft_binary_tree(line, start, i, a);
		reset_redir(a->redir);
		reset_pipe(a->pipe);
		// dup2(a->pipe->fd_backup[0], 0);
		// dup2(a->pipe->fd_backup[1], 1);
		ft_exec_tree(a->tree, a);
		if (line[i])
			i++;
	}
}

void	ft_exec_tree(t_tree *node, t_all *a)
{
    if (node->type && node->type == op_pipe)
		ft_pipe(a);
	else if (node->type && node->type == redir)
	{
		ft_redir(node->exec->op, a);
		if (node->right != NULL)
			ft_exec_tree(node->right, a);
		if (node->left != NULL)
			ft_exec_tree(node->left, a);
		return ;
	}
	else if (node->type && node->type == command)
	{
		a->pipe->another_pipe = 0;
		ft_is_another_pipe(node, a);
		ft_exec_cmd(node->exec->cmd, a);
	}
	else if (node->type && node->type == file)
		ft_file(node, a);
	if (node->left != NULL)
		ft_exec_tree(node->left, a);
	if (node->right != NULL)
		ft_exec_tree(node->right, a);
}

void	ft_file(t_tree *node, t_all *a)
{
	int fd;

	if (a->redir->chevron)
		fd = open(node->exec->file->file, O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		fd = open(node->exec->file->file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (a->redir->count == 1)
	{
		a->redir->fd_backup = dup(a->redir->fd);
		dup2(fd, a->redir->fd);
		close(fd);
	}
}

void	ft_pipe(t_all *a)
{
	init_pipe(a->pipe);
	a->pipe->count++;
}

void	ft_is_another_pipe(t_tree *node, t_all *a)
{
	if (node->e_type == op_pipe)
	{
		a->pipe->another_pipe = 1;
		return ;
	}
	if (node->left)
		ft_is_another_pipe(node->left, a);
	if (node->right)
		ft_is_another_pipe(node->right, a);
}

void	ft_redir(t_operator *op, t_all *a)
{
	a->redir->fd = ft_atoi(op->op);
	if (ft_strlen(ft_strchr(op->op, '>')) == 2)
		a->redir->chevron = 1;
	else
		a->redir->chevron = 0;
	if (!a->redir->fd)
		a->redir->fd = 1;
	a->redir->count++;
}
