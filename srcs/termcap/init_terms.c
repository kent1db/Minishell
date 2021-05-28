/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:07:44 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/28 11:49:06 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signal)
{
	t_all	*a;

	(void)signal;
	a = get_all();
	a->status_cmd = 1;
	ft_exit_status_cmd(a);
	ft_printf(1, "\n");
	display_line(a);
}

void	ft_init_termcap(t_all *a)
{
	int ret;
	char *term_type;
	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	if (ret == -1 || ret == 0)
		return (ft_error_msg("Init termcap error", a->gc));
}

void	init_termios(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~(ICANON | ECHO);
	apply_termios(termios);
}

void	init_terms(t_all *a)
{
	a->saved = get_termios();
	init_termios();
	ft_init_termcap(a);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) //|| signal(SIGINT, fct_signal) == SIG_ERR)
		return (ft_error_msg("signal have a error", a->gc));
}
