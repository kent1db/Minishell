/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garbage_collector.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 17:50:37 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/18 09:58:30 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*malloc_gc(t_list **gc, size_t size)
{
	void	*malloc_ptr;

	malloc_ptr = malloc(size);
	if (!malloc_ptr)
		ft_error_msg("Malloc error", *gc);
	ft_lstadd_front(gc, ft_lstnew(malloc_ptr));
	return (malloc_ptr);
}

char	*ft_strdup_gc(t_list **gc, char *src)
{
	char	*dest;

	dest = ft_strdup(src);
	if (!dest)
		ft_error_msg("Malloc error", *gc);
	ft_lstadd_front(gc, ft_lstnew(dest));
	return (dest);
}
