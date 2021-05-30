/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 14:42:57 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/30 21:22:59 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_add_string_in_index(t_list *gc, char *str, char *add, int index)
{
	char *s1;
	char *s2;
	char *new_str;
	
	if (!str || !add || index < 0)
		return (NULL);
	new_str = NULL;
	s1 = ft_substr(str, 0, index - 1);
	s2 = ft_substr(str, index, ft_strlen(str) - index + 1);
	new_str = ft_strjoin(s1, ft_strdup_gc(&gc, add));
	new_str = ft_strjoin_free(new_str, s2);
	ft_lstadd_front(&gc, ft_lstnew(new_str));
	free(s1);
	free(s2);
	return (new_str);
}

int	ft_print_buf(char *str, int *cursor)
{
	int	size_print;
	int	i;

	i = -1;
	size_print = 0;
	while (str[++i])
	{
		if (str[i] >= 32 || str[i] < 0)
			size_print += ft_printf(1, "%c", str[i]);
	}
	if (size_print == 0)
		return (0);
	*cursor += size_print;
	return (1);
}

void	ft_print_line_and_stock(t_all *a, char **line, char *buf, int *cursor)
{
	int	size_print;

	if (ft_print_buf(buf, cursor))
	{	
		if (!line || !(*line))
			*line = ft_strdup_gc(&a->gc, buf);
		else if (ft_strlen(*line) == (size_t)(*cursor))
			*line = ft_strjoin(*line, buf);
		else
			*line = ft_add_string_in_index(a->gc, *line, buf, *cursor);
	}
}

void	ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line)
{
	(void)a;
	ft_printf(1, "\n");
	// display_line(a);
	ft_printf(1, "➜ " CYN "minishell %s " YEL "✗ " RESET, *line);
	*cursor = 0;
	*line = NULL;
}

int	ft_switch_keyboard(t_all *a, char buf[4], int *cursor, char **line)
{
	if (buf[0] == 4)
	{
		if (*cursor == 0)
			return (1);
	}
	else if (buf[0] == 127 || buf[0] == 8)
		ft_backspace(a, cursor, line);
	else if (buf[0] == 21 && buf[1] == 0 && buf[2] == 0)
		ft_delete_line_to_cursor(a, cursor, line);
	else if (buf[1] == '[')
		ft_arrow_key(a, buf[2], cursor, line);
	else if (buf[0] == '\n')
		ft_launch_cmd_and_reset(a, cursor, line);
	else
		ft_print_line_and_stock(a, line, buf, cursor);
	return (0);
}

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