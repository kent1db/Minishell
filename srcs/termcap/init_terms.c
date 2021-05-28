/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terms.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:07:44 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/27 14:16:56 by alafranc         ###   ########lyon.fr   */
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

void	init_terms(t_all *a)
{
	a->saved = get_termios();
	delete_special_characters();
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR) //|| signal(SIGINT, fct_signal) == SIG_ERR)
		return (ft_error_msg("signal have a error", a->gc));
	init_historic(a);
}
