/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:59:58 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/08 11:51:26 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_last_op(char *line, int end, t_tree *node)
{
	int count;

	count = 0;
	if (line[end] && (line[end] == '<' ||\
	line[end] == '>' || line[end] == '|'))
	{
		while (line[end] && line[end] != ' ' && (line[end] == '<' ||\
		line[end] == '>' || line[end] == '|' || ft_isdigit(line[end])))
		{
			end--;
			count = 1;
		}
		return (end + count);
	}
	return (end + count);
}

void	ft_priority(char *line, int start, int end, t_tree *node)
{
	int	quote;

	quote = 0;
	if (node->type != file)
	{
		dprintf(1, "ici\n");
		node->type = -1;
	}
	dprintf(1, "1\n");
	ft_print_start_to_end(line, start, end);
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
}

int	ft_op_pos(char *line, int start, int end, t_tree *node)
{
	while (line[end] && end >= start)
	{
		if (line[end] == '|' && node->type == op_pipe)
			return (ft_last_op(line, end, node));
		if ((line[end] == '>' || line[end] == '<') &&\
		node->type == redir)
			return (ft_last_op(line, end, node));
		end--;
	}
	return (-1);
}
