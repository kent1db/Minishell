/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 13:46:04 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/30 17:31:04 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_arrow_key(t_all *a, char c, int *cursor, char **line)
{
	if (c == 'A')
		ft_up_arrow(a, cursor, line);
	else if (c == 'B')
		ft_down_arrow(a, cursor, line);
	else if (c == 'C')
		ft_right_arrow(cursor, *line);
	else if (c == 'D')
		ft_left_arrow(cursor);
}

void	ft_up_arrow(t_all *a, int *cursor, char **line)
{
	(void)a;
	ft_delete_line(a, cursor, line);
}

void	ft_down_arrow(t_all *a, int *cursor, char **line)
{
	(void)a;
	ft_delete_line(a, cursor, line);
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