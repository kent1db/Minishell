/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:16:13 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/08 11:30:30 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_file_name(char *line, int *tab, t_tree *node, t_all *a)
{
	int		start;
	int		end;
	char	*file;

	end = tab[1];
	start = tab[0];
	if (end == 0)
		return (NULL);
	while (line[start] && (line[start] == '>' || line[start] == '<' ||\
	line[start] == '|' || line[start] == ' '))
		start++;
	return (ft_substr(line, start, end - start));
}

void	ft_malloc_file(char *line, int *tab, t_tree *node, t_all *a)
{

	node->type = file;
	node->exec = malloc_gc(&a->gc, sizeof(t_type_union));
	node->exec->file = malloc_gc(&a->gc, sizeof(t_file));
	node->exec->file->file = ft_file_name(line, tab, node, a);
	ft_lstadd_front(&a->gc, ft_lstnew(node->exec->file->file));
	// dprintf(1, "file = %s\n", node->exec->file->file);
}
