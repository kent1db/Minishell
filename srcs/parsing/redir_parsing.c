/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 13:16:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 11:36:28 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_malloc_nb_redir(char *line, int *tab, t_all *a)
{
	int		start;
	int		count;
	char	*str;

	count = 0;
	str = malloc_gc(&a->gc, sizeof(char) * (tab[3] - tab[2] + 2));
	start = tab[2];
	while (line[start] && start <= tab[3])
		str[count++] = line[start++];
	str[count] = '\0';
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
