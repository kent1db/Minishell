/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/28 13:27:46 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_all	*set_all(t_all *tmp)
{
	static t_all	*oui;

	if (tmp)
		oui = tmp;
	return (oui);
}

t_all	*get_all(void)
{
	return (set_all(NULL));
}

t_all	*init_all(char **envp)
{
	t_all	*a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->status_cmd = 0;
	a->do_gnl = 1;
	a->env = parse_env(envp, &a->gc);
	set_all(a);
	return (a);
}

void	read_command_line(t_all *a)
{
	char	buf[4];
	int		cursor;
	t_list	*line;

	line = NULL;
	cursor = 0;
	display_line(a);
	while (read(0, buf, 3))
	{
		if (buf[0] == 127)
			ft_backspace(a, &cursor, &line);
		else if (buf[0] == 4)
			ft_printf(1, "ctrl+d");
		else if (buf[1] == '[')
		{
			if (buf[2] == 'A')
				ft_printf(1, "up");
			else if (buf[2] == 'B')
				ft_printf(1, "down");
			else if (buf[2] == 'C')
				ft_right_arrow(a, &cursor, line);
			else if (buf[2] == 'D')
				ft_left_arrow(a, &cursor);
		}
		else if (buf[0] == '\n')
		{
			ft_printf(1, "\n");
			ft_printf(1, GRN "➜ " CYN "minishell " RESET);
			ft_print_list(line);
			ft_printf(1, YEL "✗ " RESET);
			cursor = 0;
			line = NULL;
		}
		else
		{
			ft_lstadd_back(&line, ft_lstnew(ft_strdup_gc(&a->gc, buf)));
			ft_printf(1, "%s", buf);
			cursor++;
		}
		ft_bzero(buf, 3);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all	*a;	

	errno = 0;
	a = init_all(envp);
	init_terms(a);
	
	// print_banner();
	read_command_line(a);
	apply_termios(a->saved);
	ft_lstclear(&a->gc, free);
	return (0);
}
