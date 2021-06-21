/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:22:33 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/21 16:09:39 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_reverse_boolean(int boolean)
{
	if (boolean)
		return (0);
	return (1);
}

int	is_option(char *arg)
{
	int	i;

	dprintf(1, "J'ADORE LA VIE\n");
	if (!arg)
		return (0);
	i = -1;
	while (arg[++i])
	{
	ft_printf(1, "arg[%d]: %c\n", i, arg[i]);
		if (ft_is_backslash_before(arg, i, '-'))
		{
			ft_printf(1, "maybe a option\n");
			while (arg[i] == 'n' && arg[i])
				i++;
			if (arg[i])
				return (0);
			else
				return (1);
		}
	}
	return (0);
}
