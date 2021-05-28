/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/27 16:01:36 by alafranc         ###   ########lyon.fr   */
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
	char buf[256];
	char c;

	// while (buf[0] != '\n')
	// {
		while (1)
		{
			read(0, buf, 1);
			ft_printf(1, "%c", buf[0]);
			// c = getchar();
			// if (buf[0] == 279167)
				// ft_printf(1, "ohh dude");
			// ft_printf(1, "%d", buf[0]);
		}
		// read(0, &buf, 1);
		// printf("%c", buf[0]);
		// 		read(0, &buf, 1);
		// printf("%c", buf[0]);	
		// 		read(0, &buf, 1);
		// printf("%c", buf[0]);	
		// 		read(0, &buf, 1);
		// printf("%c", buf[0]);	
		// 		read(0, &buf, 1);
		// printf("%c", buf[0]);	
		// 		read(0, &buf, 1);
		// printf("%c", buf[0]);	
	// }
}
// void	read_command_line(t_all *a)
// {
// 	char	*line;

// 	line = NULL;
// 	display_line(a);
// 	while (get_next_line(0, &line))
// 	{
// 		// ft_lexing_command_line(line, a);
// 		display_line(a);
// 		free(line);
// 	}
// }

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
