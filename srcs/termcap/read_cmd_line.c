/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 14:42:57 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/01 18:23:03 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_all *a)
{
	char	buf[4];
	int		cursor;
	char	*line;

	line = NULL;
	cursor = 0;
	display_line(a);
	while (read(0, buf, 3))
	{
		if (ft_switch_keyboard(a, buf, &cursor, &line))
			break ;
		ft_bzero(buf, 3);
	}
}

int	ft_switch_keyboard(t_all *a, char buf[4], int *cursor, char **line)
{
	if (buf[0] == CTRL_D)
	{
		if (*cursor == 0)
			return (1);
	}
	else if (buf[0] == BACKSPACE || buf[0] == DEL)
		ft_backspace(&a->gc, cursor, line);
	else if (buf[0] == CTRL_U)
		ft_delete_line_to_cursor(&a->gc, cursor, line);
	else if (buf[1] == '[')
		ft_arrow_key(a, buf[2], cursor, line);
	else if (buf[0] == '\n')
		ft_launch_cmd_and_reset(a, cursor, line);
	else
		ft_print_buf_and_stock(a, line, buf, cursor);
	return (0);
}

void	ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line)
{
	(void)a;
	ft_printf(1, "\n");
	// display_line(a);
	if (*line && *line[0] != '\0')
		ft_lstadd_back(&a->termcap->historic, ft_lstnew(*line));
	ft_printf(1, "➜ " CYN "minishell %s " YEL "✗ " RESET, *line);
	*cursor = 0;
	*line = NULL;
	
	a->termcap->historic_current->content = "";
	a->termcap->ptr_historic = NULL;
}
