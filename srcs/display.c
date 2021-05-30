/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 11:44:06 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/30 17:31:24 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_banner(void)
{
	ft_printf(1, "%s    __  ________   ___________ __  __________    __\n", RED);
	ft_printf(1, "   /  |/  /  _/ | / /  _/ ___// / / / ____/ /   / /\n");
	ft_printf(1, "  / /|_/ // //  |/ // / \\__ \\/ /_/ / __/ / /   / /\n");
	ft_printf(1, " / /  / // // /|  // / ___/ / __  / /___/ /___/ /___\n");
	ft_printf(1, "/_/  /_/___/_/ |_/___//____/_/ /_/_____/_____/_____/\
		%s\n\n", RESET);
	ft_printf(1, "             by qurobert and alafranc\n\n\n");
}

void	display_line(t_all *a)
{
	t_env	*exit;
	char	*color;
	int		status_cmd;

	exit = ft_keyshr(a->env, "?");
	if (!exit)
		color = GRN;
	else
	{
		status_cmd = ft_atoi(exit->content);
		if (!status_cmd)
			color = GRN;
		else
			color = RED;
	}
	ft_printf(1, "%s➜ " CYN "minishell " YEL "✗ " RESET, color);
}

int	ft_putchar_int(int c)
{
	write(1, &c, 1);
	return (1);
}
