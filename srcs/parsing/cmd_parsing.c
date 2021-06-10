/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:12:59 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/10 15:08:05 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_ws(char *s1, char *s2, t_all *a)
{
	int		i;
	int		j;
	char	*buf;

	if (s1 == NULL)
		return (s2);
	if (s2 == NULL)
		return (s1);
	buf = malloc_gc(&a->gc, sizeof(char) * (ft_strlen(s1) +\
	ft_strlen(s2) + 2));
	if (!buf)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[j])
		buf[i++] = s1[j++];
	j = 0;
	buf[i++] = ' ';
	while (s2[j])
		buf[i++] = s2[j++];
	buf[i] = '\0';
	return (buf);
}

int	ft_re_size(char *line, int *i, int (*f)(char c, char *str), char *del)
{
	int	size;

	size = 0;
	if (f(line[*i], del) && line[*i - 1] && line[*i - 1] == ' ')
		size++;
	if (line[*i] == '>' && line[*i - 1] && ft_isdigit(line[*i - 1]))
	{
		(*i)--;
		size++;
		if (line[*i] && line[*i - 1] && ft_isdigit(line[*i - 1]))
		{
			(*i)++;
			size--;
		}
		if (line[*i] && line[*i] == ' ')
			size++;
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
	while ((!f(line[*i], del) || (f(line[*i], del) &&\
	ft_is_bs_before(line, *i))) && line[*i])
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
	return (size - ft_re_size(line, i, f, del));
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
	while (node->line[s] && !ft_delimiter(node->line[s], "><;|"))
		s++;
	if (!node->line[s] || ft_delimiter(node->line[s], "|;"))
		return (0);
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
	int		bool;

	bool = 0;
	ft_skip_whitespace(line, i);
	start = *i;
	size = ft_count_malloc(line, i, ft_delimiter, ";><|");
	node->exec->cmd->args = NULL;
	if (size <= 0)
		start = *i;
	if (size > 0)
		node->exec->cmd->args = ft_malloc_size(line, size, a, start);
	if (ft_check_arg_after(&start, &size,  node, a))
		node->exec->cmd->args = ft_strjoin_ws(node->exec->cmd->args,
		ft_malloc_size(line, size, a, start), a);
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
