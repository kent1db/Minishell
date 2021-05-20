/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:22 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/19 11:22:10 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_if_is_our_cmd(char *cmd, t_env **env, t_list **gc)
{
	return (1);
}

char	**list_cmd_done(t_list **gc)
{
	char **cmd_done;

	cmd_done = malloc_gc(gc, sizeof(char *) * 7);
	cmd_done[0] = "echo";
	cmd_done[1] = "cd";
	cmd_done[2] = "pwd";
	cmd_done[3] = "export";
	cmd_done[4] = "unset";
	cmd_done[5] = "env";
	cmd_done[6] = "exit";
	return (cmd_done);
}


void ft_lauch_cmd(char *cmds, t_all *a)
{
	int		i;
	char	**cmd_done;

	cmd_done = list_cmd_done(&a->gc);
	// i = -1;
	// while (cmds[++i])
	// {
	// 	if (!launch_if_is_our_cmd(cmds[i], a->env, a->gc))
	// 	{
			
	// 	}

	// }
}