/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:08:59 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/27 15:05:51 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_up_arrow(int a)
{
	write(1, &a, 1);
	return (1);	
}

void	init_historic(t_all *a)
{
	int ret;
	char *term_type;
	char *up_arrow;

	term_type = getenv("TERM");
	ret = tgetent(NULL, term_type);
	if (ret == -1 || ret == 0)
		return (ft_error_msg("Init termcap error", a->gc));
	up_arrow = tgetstr("ku", NULL);
	if (!up_arrow)
		return (ft_error_msg("Termcap error", a->gc));
	// *down_arrow = tgetstr("cl", NULL);
}