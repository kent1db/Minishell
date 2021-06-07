/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/07 16:35:18 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_start(char *line, int start, int i)
{
	if (i > 0)
	{
		while (line[start] && (line[start] == '>' || line[start] == '<' ||\
		line[start] == '|'))
			start++;
	}
	return (start);
}

void	ft_parsing(char *line, int *tab, t_tree *node, t_all *a)
{
	int	start;
	int	end;

	start = tab[0];
	end = tab[1];
	if (line[start] == '<' || line[start] == '>')
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
	int		op_pos;
	int		tab[3];
	static int i;

	node = malloc_gc(&a->gc, sizeof(t_tree));
	ft_priority(line, ft_start(line, start, i), end, node);
	// op_pos = ft_op_pos(line, start, end - 1, node);
	// dprintf(1, "start = %d\tend = %d\n", start, end);
	op_pos = ft_op_pos(line, start, end - 1, node);
	// dprintf(1, "type = %d\nop_pos = %d\n\n", node->type, op_pos);
	tab[0] = start;
	tab[1] = end;
	tab[2] = op_pos;
	ft_parsing(line, tab, node, a);
	// usleep(800000);
	if (op_pos > 0)
	{
		i++;
		node->left = ft_binary_tree(line, start, op_pos, a);
		node->right = ft_binary_tree(line, op_pos, end, a);
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
	int	count;
	int start;
	int	quote;

	i = 0;
	count = 0;
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
		a->tree = ft_binary_tree(line, start, i, a);
		/* exec command(a); */
		/* delete tree */
		ft_print_tree(a->tree, 0);
		if (line[i])
			i++;
	}
}
