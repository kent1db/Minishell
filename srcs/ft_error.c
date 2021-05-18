/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:50:43 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/18 09:57:22 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_msg(char *msg_error, t_list *gc)
{
	ft_printf("Error:\n%s\n", msg_error);
	exit(EXIT_FAILURE);
	ft_lstclear(&gc, free);
}
