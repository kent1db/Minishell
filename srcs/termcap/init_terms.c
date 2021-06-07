/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:07:44 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/04 13:01:12 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c(int signal)
{
	t_all	*a;

	(void)signal;
	a = get_all();
	a->status_cmd = 1;
	a->input->ctrl_c = 1;
	ft_exit_status_cmd(a);
	ft_printf(1, "\n");
	if (!a->in_cmd)
		display_line(a);
}

void	init_input(t_all *a)
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
	a->input->saved = get_termios();
	init_termios();
	init_input(a);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR || signal(SIGINT, ctrl_c) == SIG_ERR)
		return (ft_error_msg("signal have a error", a->gc));
}
