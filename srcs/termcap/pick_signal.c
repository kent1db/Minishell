/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 23:23:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/26 15:20:40 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fct_signal(int signal)
{
	
}

void	ft_pick_signal(t_all *a)
{
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_error_msg("signal have a error", a->gc);
		return ;
	}
	if (signal(SIGINT, fct_signal) == SIG_ERR)
	{
		ft_error_msg("signal have a error", a->gc);
		return ;
	}
}
