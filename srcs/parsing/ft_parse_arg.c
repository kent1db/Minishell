/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/26 13:30:15 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_malloc(char *line, int *i, int (*f)(char c, char *str), char *del)
{
	int	size;
	int	quote;

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
	return (size);
}

char	*ft_substr_sw(char *s, int w, size_t len)
{
	char	*buf;
	size_t	size;
	size_t	i;

	i = 0;
	size = 0;
	if (s == NULL)
		return (NULL);
	if (w >= ft_strlen(s))
		return (ft_calloc(1, sizeof(char)));
	while (size < len && s[w + size])
		size++;
	buf = malloc(sizeof(char) * (size + 1));
	if (!buf)
		return (NULL);
	size = 0;
	while (s[w] && i < len)
	{
		ft_is_quote(s[w], (int *)&size);
		buf[i++] = s[w++];
		if (s[w] && s[w - 1] && s[w - 1] == ' ' && s[w] == ' ' && !size)
			ft_skip_whitespace(s, &w);
	}
	buf[i] = '\0';
	return (buf);
}

char	*ft_malloc_size(char *line, int size, t_all *a, int start)
{
	char	*ptr;

	ptr = ft_substr_sw(line, start, size);
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
	size = ft_count_malloc(line, i, ft_delimiter, ";><|");
	if (size)
		arg = ft_malloc_size(line, size, a, start);
	printf("2 size = %d arg = %s\n", size, arg);
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
	size = ft_count_malloc(line, i, ft_delimiter, " ;><|\t");
	if (size)
	{
		cmd = ft_malloc_size(line, size, a, start);
		ft_malloc_argument(line, i, a, cmd);
	}
	printf("1 size = %d cmd = %s\n", size, cmd);
}

// void	ft_lexing_command_line(char *line, t_all *a)
// {
// 	int	i;
// 	int	count;
// 	int	bool;

// 	i = 0;
// 	bool = 1;
// 	count = 0;
// 	while (line[i])
// 	{
// 		if (bool)
// 			ft_malloc_command(line, &i, a, &bool);
// 		if (line[i] && (line[i] == ';' || line[i] == '|'))
// 			bool = 1;
// 		if (line[i])
// 			i++;
// 	}
// }

void	ft_parsing(char *line, int *tab, t_tree *node, t_all *a)
{
	int	start;
	int	end;

	start = tab[0];
	end = tab[1];
	if (start == '<' || start == '>')
	{
		node->exec->file->file = ft_malloc_file();
		ft_lstadd_front(&a->gc, ft_lstnew(node->exec->file->file));
	}
	else if (node->type == op_pipe)
		node->exec = NULL;
	else if (node->type = redir)
		ft_malloc_redir();
	else if (node->type == other)
		ft_malloc_command();
}

t_tree	*ft_binary_tree(char *line, int start, int end, t_all *a)
{
	t_tree	*node;
	int		op_pos;
	int		tab[2];

	node = malloc(sizeof(t_tree));
	ft_lstadd_front(&a->gc, ft_lstnew(node));
	ft_priority(line, start, end, node);
	op_pos = ft_op_pos(line, start, end, node);
	tab[0] = start;
	tab[1] = end;
	ft_parsing(line, tab, node, a);
	if (op_pos)
	{
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


	i = 0;
	count = 0;
	while (line[i])
	{
		start = i;
		a->tree->type = -1;
		while (line[i] && line[i] != ';')
			i++;
		a->tree = ft_binary_tree(line, a, start, i);
		/* exec command(a); */
		/* delete tree */
		if (line[i])
			i++;
	}
}
