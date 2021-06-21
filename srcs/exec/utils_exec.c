/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 13:46:05 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/21 13:47:22 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_tree(t_all *a)
{
	a->tree = malloc_gc(&a->gc, sizeof(t_tree));
	a->tree->type = -1;
}