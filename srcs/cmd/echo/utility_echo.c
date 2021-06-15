/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:22:33 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 16:34:24 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_reverse_boolean(int boolean)
{
	if (boolean)
		return (0);
	return (1);
}

int	is_option(char *args)
{
	int	i;

	if (!args)
		return (0);
	i = -1;
	while (args[++i])
	{
		if (ft_is_backslash_before(args, i, '-'))
		{
			while (args[i] == 'n' && args[i])
				i++;
			if (args[i])
				return (0);
			else
				return (1);
		}
	}
	return (0);
}
