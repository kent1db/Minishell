/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:16:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/08 10:04:08 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_malloc_nb_redir(char *line, int *tab, t_all *a)
{
	int		start;
	int		count;
	char	*str;

	count = 0;
	start = tab[2];
	while (line[start] && (line[start] == '>' || line[start] == '<'))
	{
		count++;
		start++;
	}
	str = malloc_gc(&a->gc, sizeof(char) * count);
	start = tab[2];
	count = 0;
	while (line[start] && (line[start] == '>' || line[start] == '<'))
		str[count++] = line[start++];
	return (str);
}

void	ft_malloc_redir(t_tree *node, t_all *a, int *tab, char *line)
{
	int start;
	int end;
	int	op_pos;

	start = 0;
	end = 0;
	op_pos = tab[2];
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->op = malloc_gc(&a->gc, sizeof(t_operator));
	node->exec->op->op = ft_malloc_nb_redir(line, tab, a);
}
