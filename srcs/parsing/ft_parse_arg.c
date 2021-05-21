/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/20 15:58:28 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_whitespace(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

int	ft_is_delimiter(char c)
{
	char	*op;
	int		i;

	i = -1;
	op = " ;><|\t";
	while (op[++i])
	{
		if (op[i] == c)
			return (1);
	}
	if (c == '\0')
		return (1);
	return (0);
}

int		ft_count_malloc(char *line, int *i)
{
	int	size;

	size = 0;
	while (!ft_is_delimiter(line[*i]))
	{
		size++;
		(*i)++;
	}
	return (size);
}

void	ft_malloc_argument(char *line, int *i, t_all *a, char *cmd)
{
	char	*arg;
	char	*opt;
	int		size;
	int		start;

	opt = malloc(sizeof(char) * 2);
	ft_skip_whitespace(line, i);
	// if (ft_strcmp("echo", cmd))
	// 	ft_malloc_option(line, i, a);
	start = *i;
	size = ft_count_malloc(line, i);
	if (size)
	{
		arg = ft_substr(line, start, size);
		ft_lstadd_front(&a->gc, ft_lstnew(arg));
	}
	ft_printf(1, "arg = %s\n", arg);
}

void	ft_malloc_command(char *line, int *i, t_all *a, int *bool)
{
	char	*cmd;
	int		size;
	int		start;

	size = 0;
	cmd = NULL;
	*bool = 0;
	ft_skip_whitespace(line, i);
	start = *i;
	size = ft_count_malloc(line, i);
	if (size)
	{
		cmd = ft_substr(line, start, size);
		ft_lstadd_front(&a->gc, ft_lstnew(cmd));
	}
	ft_malloc_argument(line, i, a, cmd);
	ft_printf(1, "cmd = %s\n", cmd);
}

void	ft_lexing_command_line(char *line, t_all *a)
{
	int	i;
	int	count;
	int	bool;

	i = -1;
	bool = 1;
	count = 0;
	while (line[++i])
	{
		if (bool)
			ft_malloc_command(line, &i, a, &bool);
		if (line[i] == ';' || line[i] == '|')
			bool = 1;
	}
}
