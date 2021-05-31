/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 13:46:04 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/01 00:06:07 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrow_key(t_all *a, char c, int *cursor, char **line)
{
	if (c == 'A')
		ft_up_arrow(a->termcap, cursor, line, &a->gc);
	else if (c == 'B')
		ft_down_arrow(a->termcap, cursor, line, &a->gc);
	else if (c == 'C')
		ft_right_arrow(cursor, *line);
	else if (c == 'D')
		ft_left_arrow(cursor);
}


t_list	*previous_current(t_list *lst, t_list *current)
{
	if (!current)
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

void	ft_up_arrow(t_termcap *term, int *cursor, char **line, t_list **gc)
{
	term->ptr_historic = previous_current(term->historic, term->ptr_historic);
	if (term->ptr_historic)
		ft_change_line(gc, cursor, line, term->ptr_historic->content);
}

void	ft_down_arrow(t_termcap *term, int *cursor, char **line, t_list **gc)
{
	if (term->ptr_historic)
	{
		term->ptr_historic = term->ptr_historic->next;
		if (!term->ptr_historic && term->historic_current)
			term->ptr_historic = ft_lstnew(term->historic_current);
		if (term->ptr_historic)
			ft_change_line(gc, cursor, line, term->ptr_historic->content);
	}	
}

void	ft_left_arrow(int *cursor)
{
	if (*cursor == 0)
		return ;
	tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	(*cursor)--;
}

void	ft_right_arrow(int *cursor, char *line)
{
	if (! line || ft_strlen(line) <= (size_t)(*cursor))
		return ;
	tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
	(*cursor)++;
}