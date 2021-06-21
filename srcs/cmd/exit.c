/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 15:37:25 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/21 15:45:48 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_exit(t_all *a, char **args)
{
	(void)args;
	ft_printf(1, "j'existe les gars\n");
	a->read = 0;
	return (0);
}