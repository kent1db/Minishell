/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 11:00:12 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reverse_booleanean(int booleanean)
{
	if (booleanean)
		return (0);
	return (1);
}

int	is_option()
{
	return (1);

}

int	find_arguments()
{
	return (1);

}
// echo -n -nnnnnnn -nnnnnnnnn -nrw => rw
// echo -n -nnnnn hello -n ; echo a => hello na
int	ft_echo(t_all *a, t_command *cmd)
{
	int	i;
	int	quote;
	int	option;

	(void)a;
	quote = 0;
	option = 0;
	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i] == '\"')
			ft_reverse_booleanean(quote);
		else if (cmd->args[i] == '\'')
			ft_reverse_booleanean(quote);
		else
		{
			
		}
	}
	// if (!cmd->opt || (cmd->opt && ft_strcmp("-n", cmd->opt)))
		ft_printf(1, "\n");
	return (0);
}
