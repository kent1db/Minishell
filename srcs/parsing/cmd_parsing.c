/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:12:59 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 16:12:50 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_re_size(char *line, int *i, int (*f)(char c, char *str), int size)
{
	if (line[*i] == '>')
	{
		(*i)--;
		size--;
		while (line[*i] && ft_isdigit(line[*i]))
		{
			(*i)--;
			size--;
		}
	}
	return (size);
}

int	ft_count_malloc(char *line, int *i, int (*f)(char c, char *str), char *del)
{
	int	size;
	int	quote;
	int	a;

	size = 0;
	quote = 0;
	while (!f(line[*i], del) && line[*i])
	{
		ft_is_quote(line[*i], &quote);
		if (line[*i] == ' ' && !quote)
		{
			(*i)++;
			size++;
			ft_skip_whitespace(line, i);
		}
		else
		{
			size++;
			(*i)++;
		}
	}
	if (f(line[*i], del) && line[*i - 1] && line[*i - 1] == ' ')
		size--;
	else
		size = ft_re_size(line, i, f, size);
	return (size);
}

char	*ft_malloc_size(char *line, int size, t_all *a, int start)
{
	char	*ptr;

	ptr = ft_substr_sw(line, start, size);
	if (!ptr)
		ft_error_msg("Malloc error", a->gc);
	ft_lstadd_front(&a->gc, ft_lstnew(ptr));
	return (ptr);
}

int		ft_check_arg_after(int *start, int *size, t_tree *node, t_all *a)
{
	int	s;
	int beg;
	int end;

	s = (*start);
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
		*start = beg;
		*size = end - beg;
		return (1);
	}
	return (0);
}

void	ft_malloc_argument(char *line, int *i, t_all *a, t_tree *node)
{
	int		size;
	int		start;
	
	ft_skip_whitespace(line, i);
	start = *i;
	size = ft_count_malloc(line, i, ft_delimiter, ";><|");
	if (size <= 0)
		start = *i;
	if (size > 0)
		node->exec->cmd->args = ft_malloc_size(line, size, a, start);
	else if (ft_check_arg_after(&start, &size,  node, a))
		node->exec->cmd->args = /*ft_strjoin(node->exec->cmd->args, */ft_malloc_size(line, size, a, start);
	else
		node->exec->cmd->args = NULL;
}

int	ft_malloc_command(char *line, int *tab, t_tree *node, t_all *a)
{
	int		size;
	int		start;

	size = 0;
	ft_skip_whitespace(line, &tab[0]);
	start = tab[0];
	size = ft_count_malloc(line, &start, ft_delimiter, " ;><|\t");
	if (size > 0)
	{
		node->type = command;
		node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
		node->exec->cmd = malloc_gc(&a->gc, sizeof(t_command));
		node->exec->cmd->cmd = ft_malloc_size(line, size, a, tab[0]);
		ft_malloc_argument(line, &start, a, node);
		return (1);
	}
	else
		node->exec = NULL;
	return (0);
}
