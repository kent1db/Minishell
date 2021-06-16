/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:47:52 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/16 15:39:06 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_all *a)
{
	a->fd = 1;
	a->fd_b = malloc_gc(&a->gc, sizeof(int) * 3);
	a->fd_p = malloc_gc(&a->gc, sizeof(int) * 2);
	a->fd_b[0] = dup(0);
	a->fd_b[1] = dup(1);
	a->fd_b[2] = dup(2);
	if (pipe(a->fd_p) == -1)
		ft_printf(2, "pipe failed\n");
}
