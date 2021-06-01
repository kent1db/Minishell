/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:08:59 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/01 18:09:38 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*previous_current(t_list *lst, t_list *current, t_list *historic_current)
{
	if (!current || current == historic_current)
		return (ft_lstlast(lst));
	if (lst == current)
		return (lst);
	while (lst->next)
	{
		if (lst->next == current)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	ft_change_line(t_list **gc, int *cursor, char **line, char *new_line)
{
	ft_delete_line(gc, cursor, line);
	*line = ft_strdup_gc(gc, new_line);	
	*cursor = ft_strlen(*line);
	ft_printf(1, "%s", new_line);
}

char	*ft_add_string_in_index(t_list *gc, char *str, char *add, int index)
{
	char *s1;
	char *s2;
	char *new_str;
	
	if (!str || !add || index < 0)
		return (str);
	s1 = ft_substr(str, 0, index - 1);
	s2 = ft_substr(str, index, ft_strlen(str) - index + 1);
	new_str = ft_strjoin(s1, ft_strdup_gc(&gc, add));
	new_str = ft_strjoin_free(new_str, s2);
	ft_lstadd_front(&gc, ft_lstnew(new_str));
	free(s1);
	free(s2);
	return (new_str);
}
