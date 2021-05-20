/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_array_our_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 10:50:09 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/20 10:50:33 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	**list_cmd_done(t_list **gc)
{
	int	nb_cmd;
	char **cmd_done;

	nb_cmd = 7;
	cmd_done = malloc_gc(gc, sizeof(char *) * (nb_cmd + 1));
	cmd_done[0] = ft_strdup_gc(gc, "echo");;
	cmd_done[1] = ft_strdup_gc(gc, "cd");;
	cmd_done[2] = ft_strdup_gc(gc, "pwd");;
	cmd_done[3] = ft_strdup_gc(gc, "export");;
	cmd_done[4] = ft_strdup_gc(gc, "unset");;
	cmd_done[5] = ft_strdup_gc(gc, "env");;
	cmd_done[6] = ft_strdup_gc(gc, "exit");;
	cmd_done[7] = NULL;
	return (cmd_done);
}


void	*init_array_instruction_function(t_list **gc)
{
	int	(**ft_cmd)(t_all *a);
	int		nb_cmd;

	nb_cmd = 7;
	ft_cmd = malloc_gc(gc, sizeof(ft_cmd) * nb_cmd);
	ft_cmd[0] = NULL;
	ft_cmd[1] = NULL;
	ft_cmd[2] = NULL;
	ft_cmd[3] = &ft_export;
	ft_cmd[4] = &ft_unset;
	ft_cmd[5] = &ft_env;
	ft_cmd[6] = NULL;
	return (ft_cmd);
}
