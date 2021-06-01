/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 13:46:04 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/01 18:09:24 by alafranc         ###   ########lyon.fr   */
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

void	ft_up_arrow(t_termcap *term, int *cursor, char **line, t_list **gc)
{
	term->ptr_historic = previous_current(term->historic, term->ptr_historic, term->historic_current);
	if (term->ptr_historic)
		ft_change_line(gc, cursor, line, term->ptr_historic->content);
}

void	ft_down_arrow(t_termcap *term, int *cursor, char **line, t_list **gc)
{
	if (term->ptr_historic)
	{
		if (term->ptr_historic == term->historic_current)
			return ;
		term->ptr_historic = term->ptr_historic->next;
		if (!term->ptr_historic && term->historic_current)
		 	term->ptr_historic = term->historic_current;
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
	if (!line || ft_strlen(line) <= (size_t)(*cursor))
		return ;
	tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
	(*cursor)++;
}