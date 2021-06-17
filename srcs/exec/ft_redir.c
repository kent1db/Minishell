/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:44:32 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/17 12:59:13 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	ft_redir(t_operator *op, t_all *a)
{
	a->redir->fd = ft_atoi(op->op);
	if (ft_strlen(ft_strchr(op->op, '>')) == 2)
		a->redir->chevron = 1;
	else
		a->redir->chevron = 0;
	if (!a->redir->fd)
		a->redir->fd = 1;
	a->redir->count++;
}	