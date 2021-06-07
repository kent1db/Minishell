/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/04 14:10:18 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reverse_boolean(int boolean)
{
	if (boolean)
		return (0);
	return (1);
}

// echo -n -nnnnnnn -nnnnnnnnn -nrw => rw
// echo -n -nnnnn hello -n ; echo a => hello na
int	ft_echo(t_all *a, t_command *cmd)
{
	int	i;
	int	parenthesis;
	int	quote;
	int	d_quote;
	int	dollar;

	(void)a;
	quote = 0;
	d_quote = 0;
	parenthesis = 0;
	i = -1;
	while (cmd->args[++i])
	{
		if (cmd->args[i] == '\"')
			ft_reverse_boolean(d_quote);
		else if (cmd->args[i] == '\'')
			ft_reverse_boolean(quote);
		else if (cmd->args[i] == '(')
			parenthesis = 1;
		else if (cmd->args[i] == ')')
			parenthesis = 0;
		else
		{
			
		}
	}
	if (!cmd->opt || (cmd->opt && ft_strcmp("-n", cmd->opt)))
		ft_printf(1, "\n");
	return (0);
}
