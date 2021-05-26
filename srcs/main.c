/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/26 08:24:29 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_all *a)
{
	char	*line;

	line = NULL;
	ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		// ft_lexing_command_line(line, a);
		ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

t_all	*init_all(char **envp)
{
	t_all *a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->status_cmd = 0;
	a->env = parse_env(envp, &a->gc);
	return (a);
}

int	ft_print_puts(int c)
{
	write(1, &c, 1);
	return (1);
}
void	learn_termcap(t_all *a)
{
	char *term_type;
	char *buf_termcap;
	int ret;

	term_type = getenv("TERM");
	ret = tgetent(buf_termcap, term_type);
	if (ret == -1 || ret == 0)
		ft_error_msg("Error termcap", a->gc);
	char *str = tgetstr("cm",NULL);
	tputs(tgoto(str, 5, 5), 1, ft_print_puts);
	// for(int i = 0 ; str[i] != '\0'; i++)
	// {
	// 	if (str[i] == '\x1b')
	// 		putchar('E');
	// 	else
    //         putchar(str[i]);
	// }
	// ft_printf(1, "HO REGARDE JE SUIS EN VERT\n");
	// char *reset_cmd = tgetstr("me", NULL);
	// tputs(reset_cmd, 1, putchar);
}

int	main(int ac, char **av, char **envp)
{
	t_all *a;

	errno = 0;
	a = init_all(envp);
	learn_termcap(a);
	// print_banner();
	// ft_pick_signal(a);
    read_command_line(a);

	// ft_launch_cmd("./ls", a, av[0]);
	// ft_exit_status_cmd(a);
	// ft_printf(1, "echo $? : %s", ft_keyshr(a->env, "?")->content);
	ft_lstclear(&a->gc, free);
	return (0);
}