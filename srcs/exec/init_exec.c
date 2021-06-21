/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/18 13:30:07 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/21 15:07:10 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_pipe(t_pipe *pipe)
{
	pipe->another_cmd = 0;
	pipe->count = 0;
	pipe->is_pipe = 0;
	init_pipe(pipe);
}

void	reset_redir(t_redir *redir)
{
	redir->count = 0;
	init_redir(redir);
	dup2(redir->fd_backup, redir->fd);
	init_redir(redir);
}

void	init_pipe(t_pipe *pipe)
{
	pipe->fd_backup[0] = dup(0);
	pipe->fd_backup[1] = dup(1);
	pipe->fd_backup[2] = dup(2);
	pipe->backup_tmp = 0;
}

void	init_redir(t_redir *redir)
{
	redir->fd_backup = -1;
	redir->chevron = 0;
	redir->fd = -1;
}
