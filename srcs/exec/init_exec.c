/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:30:07 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/23 14:13:12 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_redir(t_all *a)
{
	// dprintf(1, "1\n");
	dup2(a->pipe->fd_backup[0],0);
	dup2(a->pipe->fd_backup[1],1);
	dup2(a->pipe->fd_backup[2],2);
	init_redir(a->redir);
}

void	init_pipe(t_pipe *pipe)
{
	pipe->count = 0;
	pipe->is_pipe = 0;
	pipe->fd_backup[0] = dup(0);
	pipe->fd_backup[1] = dup(1);
	pipe->fd_backup[2] = dup(2);
	pipe->backup_tmp = 0;
}

void	init_redir(t_redir *redir)
{
	redir->count = 0;
	redir->chevron = 0;
	redir->fd = -1;
}
