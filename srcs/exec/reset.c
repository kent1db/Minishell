/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:57:57 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/24 14:47:00 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(t_all *a)
{
	t_fd	*next;

	while (a->fd != NULL)
	{
		next = a->fd->next;
		close(a->fd->content);
		free(a->fd);
		a->fd = next;
	}
}

void	ft_reset(t_all *a)
{
	reset_redir(a);
	init_pipe(a->pipe);
	ft_close_fd(a);
}

void	ft_lst_add_fd(t_all *a, int fd)
{
	t_fd	*elem;

	if (a->fd == NULL)
	{
		a->fd = malloc(sizeof(t_fd));
		if (!a->fd)
		{
			ft_lstclear(&a->gc, free);
			exit(EXIT_FAILURE);
		}
		a->fd->content = fd;
		a->fd->next = NULL;
	}
	else
	{
		elem = malloc(sizeof(t_fd));
		if (!elem)
		{
			ft_lstclear(&a->gc, free);
			exit(EXIT_FAILURE);
		}
		elem->content = fd;
		elem->next = a->fd;
		a->fd = elem;
	}
}
