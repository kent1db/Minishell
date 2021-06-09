/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:59:58 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 14:17:34 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_is_file(char *line, int start)
{
	if (start > 0)
	{
		while (start > 0 && line[start] == ' ')
			start--;
		if (line[start] && (line[start] == '>' || line[start] == '<'))
			return (1);
	}
	return (0);
}

int		*ft_tab_op(char *line, int end, t_tree *node, t_all *a)
{
	int count;
	int	*op_pos;

	count = 0;
	op_pos = malloc_gc(&a->gc, sizeof(int) * 2);
	if (line[end] && (line[end] == '<' ||\
	line[end] == '>' || line[end] == '|'))
	{
		op_pos[1] = end;
		while (line[end] && line[end] != ' ' && (line[end] == '<' ||\
		line[end] == '>' || line[end] == '|' || ft_isdigit(line[end])))
		{
			end--;
			count = 1;
		}
		op_pos[0] = end + count;
	}
	else
	{
		op_pos[0] = -1;
		op_pos[1] = -1;
	}
	return (op_pos);
}

void	ft_priority(char *line, int start, int end, t_tree *node)
{
	int	quote;
	int	beg;

	quote = 0;
	node->type = -1;
	beg = start;
	while (line[start] && start < end)
	{
		ft_is_quote(line[start], &quote);
		if (line[start] == '|' && !quote)
			node->type = op_pipe;
		else if ((line[start] == '>'  || line[start] == '<') &&\
		node->type < redir && !quote)
			node->type = redir;
		else if (node->type < other && !quote)
			node->type = other;
		start++;
	}
	if (ft_is_file(line, beg) && node->type == other)
		node->type = file;
}

int		*ft_op_pos(char *line, int end, t_tree *node, t_all *a)
{
	while (line[end] && end >= node->start)
	{
		if (line[end] == '|' && node->type == op_pipe)
			return (ft_tab_op(line, end, node, a));
		if ((line[end] == '>' || line[end] == '<') &&\
		node->type == redir)
			return (ft_tab_op(line, end, node, a));
		end--;
	}
	return (ft_tab_op(line, end, node, a));
}
