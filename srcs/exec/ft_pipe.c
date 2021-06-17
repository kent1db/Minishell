/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:47:52 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/17 13:35:22 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pipe(t_all *a)
{
	a->pipe->boolean = 1;
	a->pipe->fd_backup[0] = dup(0);
	a->pipe->fd_backup[1] = dup(1);
	a->pipe->fd_backup[2] = dup(2);
	if (pipe(a->pipe->fd) == -1)
		ft_printf(2, "pipe failed\n");
}
