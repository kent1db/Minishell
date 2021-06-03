/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/03 13:44:23 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_echo(t_all *a, t_command *cmd)
{
	(void)a;
	ft_printf(1, "%s", cmd->args);
	if (!cmd->opt || (cmd->opt && ft_strcmp("-n", cmd->opt)))
		ft_printf(1, "\n");
	return (0);
}
