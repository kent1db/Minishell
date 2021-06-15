/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_array_fct_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/21 13:12:49 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 12:48:36 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**list_cmd_done(t_list **gc)
{
	int		nb_cmd;
	char	**cmd_done;

	nb_cmd = 9;
	cmd_done = malloc_gc(gc, sizeof(char *) * (nb_cmd + 1));
	cmd_done[0] = ft_strdup_gc(gc, "echo");
	cmd_done[1] = ft_strdup_gc(gc, "cd");
	cmd_done[2] = ft_strdup_gc(gc, "pwd");
	cmd_done[3] = ft_strdup_gc(gc, "export");
	cmd_done[4] = ft_strdup_gc(gc, "unset");
	cmd_done[5] = ft_strdup_gc(gc, "env");
	cmd_done[6] = ft_strdup_gc(gc, "exit");
	cmd_done[7] = ft_strdup_gc(gc, "alexis");
	cmd_done[8] = ft_strdup_gc(gc, "quentin");
	cmd_done[9] = NULL;
	return (cmd_done);
}

void	*init_array_instruction_function(t_list **gc)
{
	int		(**ft_cmd)(t_all *a, char *args);
	int		nb_cmd;

	nb_cmd = 9;
	ft_cmd = malloc_gc(gc, sizeof(ft_cmd) * (nb_cmd + 1));
	ft_cmd[0] = &ft_echo;
	ft_cmd[1] = &ft_cd;
	ft_cmd[2] = &ft_pwd;
	ft_cmd[3] = &ft_export;
	ft_cmd[4] = &ft_unset;
	ft_cmd[5] = &ft_env;
	ft_cmd[6] = &ft_exit;
	ft_cmd[7] = &ft_alexis;
	ft_cmd[8] = &ft_quentin;
	ft_cmd[9] = NULL;
	return (ft_cmd);
}

char	**fill_argument_execve(t_all *a, char *args)
{
	char	**arg;
	char	**arg_cmd_split;
	int		i;
	
	i = -1;
	arg = malloc_gc(&a->gc, sizeof(char *) * 2);
	if (!arg)
		ft_error_msg("Malloc error", a->gc);
	arg[0] = a->name_prg;
	arg[1] = NULL;
	if (!args || (args && args[0] == '\0'))
		return (arg);
	arg_cmd_split = ft_split(args, ' ');
	ft_strs_add_to_gc(arg_cmd_split, &a->gc);
	while (++i < ft_strslen(arg_cmd_split))
	{
		arg = ft_strsjoin(arg, arg_cmd_split[i]);
		ft_strs_add_to_gc(arg, &a->gc);
	}
	return (arg);
}
