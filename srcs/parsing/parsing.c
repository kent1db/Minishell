/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 16:06:24 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_cmd_after(int **tab, t_tree *node, t_all *a)
{
	int	s;
	int beg;
	int end;

	s = node->start;
	while (node->line[s] && ft_delimiter(node->line[s], " ><123456789"))
		s++;
	while (node->line[s] && !ft_delimiter(node->line[s], " ><|;"))
		s++;
	while (node->line[s] && node->line[s] == ' ')
		s++;
	beg = s;
	while (node->line[s] && !ft_delimiter(node->line[s], "><|;"))
		s++;
	end = s;
	if (end - beg > 0)
	{
		(*tab)[0] = beg;
		(*tab)[1] = end;
		return (1);
	}
	return (0);
}

void	ft_put_in_tab(int **tab, int *op_pos, t_tree *node, t_all *a)
{
	(*tab) = malloc_gc(&a->gc, sizeof(int) * 4);
	if (node->type == -1)
	{
		if (ft_check_cmd_after(tab, node, a))
			node->type = 0;
	}
	else
	{
		(*tab)[0] = node->start;
		(*tab)[1] = node->end;
	}
	(*tab)[3] = op_pos[1];
	(*tab)[2] = op_pos[0];
}

void	ft_parsing(char *line, int *tab, t_tree *node, t_all *a)
{
	int	start;
	int	end;

	start = tab[0];
	end = tab[1];
	if (node->type == file)
		ft_malloc_file(line, tab, node, a);
	else if (node->type == op_pipe)
		node->exec = NULL;
	else if (node->type == redir)
		ft_malloc_redir(node, a, tab, line);
	else if (node->type == other)
		ft_malloc_command(line, tab, node, a);
			// dprintf(1, "cmd = %s\targs = %s\n", node->exec->cmd->cmd, node->exec->cmd->args);
	// dprintf(1, "\n");
}

t_tree	*ft_binary_tree(char *line, int start, int end, t_all *a)
{
	t_tree	*node;
	int		*op_pos;
	int		*tab;

	node = malloc_gc(&a->gc, sizeof(t_tree));
	ft_priority(line, start, end, node);
	node->start = start;
	node->end = end;
	node->line = line;
	op_pos = ft_op_pos(line, end - 1, node, a);
	ft_put_in_tab(&tab, op_pos, node, a);
	// dprintf(1, "type = %d\nop_pos[0] = %d\top_pos[1] = %d\n\n", node->type, op_pos[0], op_pos[1]);
	ft_parsing(line, tab, node, a);
	// usleep(800000);
	if (node->type == op_pipe || node->type == redir)
	{
		a->tree->loop++;
		node->left = ft_binary_tree(line, start, op_pos[0] - 1, a);
		node->right = ft_binary_tree(line, op_pos[1] + 1, end, a);
	}
	else
	{
		node->left = NULL;
		node->right = NULL;
	}
	return (node);
}

void	ft_lexing_command_line(char *line, t_all *a)
{
	int	i;
	int start;
	int	quote;

	i = 0;
	quote = 0;
	while (line[i])
	{
		ft_printf(1, "\n\n BINARY TREE \n\n");
		start = i;
		a->tree->type = -1;
		while (line[i])
		{
			ft_is_quote(line[i], &quote);
			if (line[i] == ';' && !quote)
				break ;
			i++;
		}
		a->tree->loop = 0;
		a->tree = ft_binary_tree(line, start, i, a);
		/* exec command(a); */
		/* delete tree */
		ft_print_tree(a->tree, 0);
		if (line[i])
			i++;
	}
}
