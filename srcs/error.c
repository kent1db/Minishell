/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 19:50:43 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/21 13:32:29 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_msg(char *msg_error, t_list *gc)
{
	ft_printf(1, "Error:\n%s\n", msg_error);
	exit(EXIT_FAILURE);
	ft_lstclear(&gc, free);
}