/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/21 14:49:09 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_skip_whitespace(char *line, int *i)
{
	while (line[*i] && (line[*i] == ' ' || line[*i] == '\t'))
		(*i)++;
}

int	ft_delimiter_arg(char c)
{
	char		*del;
	int			i;
	static int	quote;

	i = -1;
	del = ";><|";
	if (!quote && (c ==  '\'' || c == '\"'))
		quote = 1;
	else if (quote && (c ==  '\'' || c == '\"'))
		quote = 0;
	while (del[++i])
	{
		if (del[i] == c && !quote)
			return (1);
	}
	if (c == '\0')
		return(1);
	return (0);
}

int	ft_delimiter_cmd(char c)
{
	char	*del;
	int		i;

	i = -1;
	del = " ;><|\t";
	while (del[++i])
	{
		if (del[i] == c)
			return (1);
	}
	if (c == '\0')
		return(1) ;
	return (0);
}

int		ft_count_malloc(char *line, int *i, int (*f)(char c))
{
	int	size;

	size = 0;
	while (!f(line[*i]))
	{
		// if (line[*i] == ' ')
		// {
		// 	(*i)++;
		// 	while (line[*i] == ' ')
		// 		(*i)++;
		// }
		size++;
		(*i)++;
	}
	return (size);
}

char	*ft_malloc_size(char *line, int size, t_all *a, int start)
{
	char	*ptr;

	ptr = ft_substr(line, start, size);
	ft_lstadd_front(&a->gc, ft_lstnew(ptr));
	return (ptr);
}

void	ft_malloc_argument(char *line, int *i, t_all *a, char *cmd)
{
	char	*arg;
	char	*opt;
	int		size;
	int		start;

	arg = NULL;
	opt = malloc(sizeof(char) * 2);
	ft_skip_whitespace(line, i);
	// if (ft_strcmp("echo", cmd))
	// 	ft_malloc_option(line, i, a);
	start = *i;
	size = ft_count_malloc(line, i, ft_delimiter_arg);
	if (size)
		arg = ft_malloc_size(line, size, a, start);
	ft_printf(1, "size = %d arg = %s\n", size, arg);
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
	size = ft_count_malloc(line, i, ft_delimiter_cmd);
	if (size)
		cmd = ft_malloc_size(line, size, a, start);
	ft_malloc_argument(line, i, a, cmd);
	ft_printf(1, "size = %d cmd = %s\n", size,  cmd);
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
