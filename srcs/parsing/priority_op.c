/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   priority_op.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:59:58 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/07 16:31:59 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_start_to_end(char *line, int start, int end)
{
	int	i;

	i = 0;
	while (line[start] && start != end)
	{
		write(1, &line[start], 1);
		start++;
	}
	write(1, "\n", 1);
}

int		ft_last_op(char *line, int end)
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

void	ft_priority(char *line, int start, int end,  t_tree *node)
{
	int	quote;

	quote = 0;
	node->type = -1;
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
	while (line[end] && end > start)
	{
		if (line[end] == '|' && node->type == op_pipe)
			return (ft_last_op(line, end));
		if ((line[end] == '>' || line[end] == '<') &&\
		node->type == redir)
			return (ft_last_op(line, end));
		end--;
	}
	return (-1);
}
