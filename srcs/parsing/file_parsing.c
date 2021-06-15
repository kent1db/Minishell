/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:16:13 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/15 11:00:35 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_file_name(char *line, int *array, t_tree *node, t_all *a)
{
	int		start;
	int		end;
	int		ws;

	(void)node;
	(void)a;
	end = array[1];
	start = array[0];
	while (line[start] && (line[start] == '>' || line[start] == '<' ||\
	line[start] == ' '))
		start++;
	ws = ft_strchr_index(&line[start], ' ');
	return (ft_substr(line, start, ws));
}

void	ft_malloc_file(char *line, int *array, t_tree *node, t_all *a)
{
	node->type = file;
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->file = malloc_gc(&a->gc, sizeof(t_file));
	node->exec->file->file = ft_file_name(line, array, node, a);
	ft_lstadd_front(&a->gc, ft_lstnew(node->exec->file->file));
}
