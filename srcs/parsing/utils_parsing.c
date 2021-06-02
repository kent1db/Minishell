/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 09:59:21 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/02 10:07:47 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_whitespace(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

void	ft_is_quote(char c, int *quote)
{
	if (!(*quote) && (c == '\'' || c == '\"'))
		*quote = 1;
	else if (*quote && (c == '\'' || c == '\"'))
		*quote = 0;
}

int	ft_delimiter(char c, char *del)
{
	int			i;
	static int	quote;

	i = -1;
	ft_is_quote(c, &quote);
	while (del[++i])
	{
		if (del[i] == c && !quote)
			return (1);
	}
	if (c == '\0')
		return (1);
	return (0);
}

void	ft_priority(char *line, int start, int end,  t_tree *node)
{
	node->type = -1;
	while (line[start] && start < end)
	{
		if (line[start] == '|')
			node->type = op_pipe;
		else if ((line[start] == '>'  || line[start] == '<') &&\
		node->type < redir)
			node->type = redir;
		else if (node->type < other)
			node->type = other;
		start++;
	}
}

int	ft_op_pos(char *line, int start, int end, t_tree *node)
{
	while (line[end] && end > start)
	{
		if (line[end] == '|' && node->type == op_pipe)
			return (end);
		if ((line[end] == '>' || line[end] == '<') &&\
		node->type == redir)
			return (end);
		end--;
	}
	return (-1);
}