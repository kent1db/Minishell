/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:16:13 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 14:49:25 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_file_name(char *line, int *tab, t_tree *node, t_all *a)
{
	int		start;
	int		end;
	char	*file;
	int		ws;

	end = tab[1];
	start = tab[0];
	while (line[start] && (line[start] == '>' || line[start] == '<' ||\
	line[start] == ' '))
		start++;
	ws = ft_strchr_index(&line[start], ' ');
	return (ft_substr(line, start, ws));
}

void	ft_malloc_file(char *line, int *tab, t_tree *node, t_all *a)
{
	node->type = file;
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->file = malloc_gc(&a->gc, sizeof(t_file));
	node->exec->file->file = ft_file_name(line, tab, node, a);
	ft_lstadd_front(&a->gc, ft_lstnew(node->exec->file->file));
}
