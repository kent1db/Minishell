/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/02 16:05:16 by qurobert         ###   ########lyon.fr   */
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
	if (!ptr)
		ft_error_msg("Malloc error", a->gc);
	ft_lstadd_front(&a->gc, ft_lstnew(ptr));
	return (ptr);
}

void	ft_malloc_argument(char *line, int *i, t_all *a, t_tree *node)
{
	int		size;
	int		start;
	
	ft_skip_whitespace(line, i);
	// if (ft_strcmp("echo", cmd))
	// 	ft_malloc_option(line, i, a);
	start = *i;
	size = ft_count_malloc(line, i, ft_delimiter, ";><|");
	if (size)
		node->exec->cmd->args = ft_malloc_size(line, size, a, start);
}

void	ft_malloc_command(char *line, int *tab, t_tree *node, t_all *a)
{
	int		size;
	int		start;

	size = 0;
	ft_skip_whitespace(line, &tab[0]);
	start = tab[0];
	size = ft_count_malloc(line, &start, ft_delimiter, " ;><|\t");
	if (size)
	{
		node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
		node->exec->cmd = malloc_gc(&a->gc, sizeof(t_command));
		node->exec->cmd->cmd = ft_malloc_size(line, size, a, tab[0]);
		ft_malloc_argument(line, &start, a, node);
	}
}

void	ft_malloc_redir(t_tree *node, t_all *a, int *tab, char *line)
{
	int start;
	int end;
	int	op_pos;

	start = tab[0];
	end = tab[1];
	op_pos = tab[2];
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->op = malloc_gc(&a->gc, sizeof(t_operator));
	if (line[op_pos] == '<')
	{
		node->exec->op->op = malloc_gc(&a->gc, (sizeof(char) * 2));
		ft_strcpy(node->exec->op->op, "<");
	}
	else
	{
		node->exec->op->op = malloc_gc(&a->gc, (sizeof(char) * 2));
		ft_strcpy(node->exec->op->op, ">");
	}
	dprintf(1, "redirection = %s\n", node->exec->op->op);
}

void	ft_malloc_file(char *line, int *tab, t_tree *node, t_all *a)
{
	int start;
	int end;

	end = tab[1];
	start = tab[0] + 1;
	node->type = other;
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->file = malloc_gc(&a->gc, sizeof(t_file));
	node->exec->file->file = ft_substr(line, start, end - start);
	dprintf(1, "file = %s\n", node->exec->file->file);
}

void	ft_parsing(char *line, int *tab, t_tree *node, t_all *a)
{
	int	start;
	int	end;

	start = tab[0];
	end = tab[1];
	if (line[start] == '<' || line[start] == '>')
	{
		ft_malloc_file(line, tab, node, a);
	}
	else if (node->type == op_pipe)
	{
		node->exec = NULL;
	}
	else if (node->type == redir)
	{
		ft_malloc_redir(node, a, tab, line);
	}
	else if (node->type == other)
	{
		ft_malloc_command(line, tab, node, a);
		dprintf(1, "cmd = %s\targs = %s\n", node->exec->cmd->cmd, node->exec->cmd->args);
	}
	dprintf(1, "\n");
}

t_tree	*ft_binary_tree(char *line, int start, int end, t_all *a)
{
	t_tree	*node;
	int		op_pos;
	int		tab[3];
	// static int i;

	node = malloc_gc(&a->gc, sizeof(t_tree));
	// node->count = 0;
	// if (i > 0)
	// 	node->count = 1;
	ft_priority(line, start + 1 /*node->count*/, end, node);
	op_pos = ft_op_pos(line, start, end - 1, node);
	dprintf(1, "type = %d\nop_pos = %d\n", node->type, op_pos);
	tab[0] = start;
	tab[1] = end;
	tab[2] = op_pos;
	ft_parsing(line, tab, node, a);
	if (op_pos > 0)
	{
		// i++;
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
		a->tree = ft_binary_tree(line, start, i, a);
		/* exec command(a); */
		/* delete tree */
		if (line[i])
			i++;
	}
	// ft_print_tree(a->tree, 0);
}

void	ft_print_tree(t_tree *node, int count)
{
	// if (node->type == op_pipe)
	// 	ft_printf(1, "node %d : pipe\n", count);
	// else if (node->type == redir)
	// 	ft_printf(1, "node %d : redir : %s\n", count, node->exec->op->op);
	// else if (node->exec->file)
	// 	ft_printf(1, "node %d : file : %s\n", count, node->exec->file->file);
	// dprintf(1, "%d_type = %d\n other = %d\n", count, node->type, other);
	if (node->type == other)
		ft_printf(1, "node %d : cmd = %s\t arg = %s\n", count, node->exec->cmd->cmd, node->exec->cmd->args);
	if (node->left != NULL)
		ft_print_tree(node->left, count + 1);
	if (node->right != NULL)
		ft_print_tree(node->right, count + 1);
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