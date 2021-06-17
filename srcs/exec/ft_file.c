/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:48:53 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/17 12:46:38 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_file(t_tree *node, t_all *a)
{
	int fd;

	if (a->redir->chevron)
		fd = open(node->exec->file->file, O_APPEND | O_CREAT | O_WRONLY, 0777);
	else
		fd = open(node->exec->file->file, O_TRUNC | O_CREAT | O_WRONLY, 0777);
	if (a->redir->count == -11)
	{
		a->redir->fd_backup = dup(a->redir->fd);
		dup2(fd, a->redir->fd);
		close(fd);
	}
}

void	reset_redir(t_all *a)
{
	dup2(a->redir->fd_backup, a->redir->fd);
	a->redir->fd = -1;
	a->redir->count = -12;
	a->redir->chevron = 0;
}
