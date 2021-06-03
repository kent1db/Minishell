/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:22 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/03 11:15:28 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_point_gc_on_split(t_list **gc, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		ft_lstadd_front(gc, ft_lstnew(split[i]));
	ft_lstadd_front(gc, ft_lstnew(split));
}

void	ft_print_strs(char **path_cmd)
{
	int	i;

	i = 0;
	ft_printf(1, "\n");
	if (!path_cmd)
		ft_printf(1, "IS NULL");
	while (path_cmd[i])
	{
		ft_printf(1, "path_cmd[%d]: %s\n", i, path_cmd[i]);
		i++;
	}
}

int	ft_launch_execve_with_path(char *path_cmd, t_all *a, char **arg)
{
	struct stat	buf;
	int			status;

	if (lstat(path_cmd, &buf) == 0)
	{
		if (fork() == 0)
		{
			execve(path_cmd, arg, convert_env_to_strs(&a->gc, a->env));
			exit(0);
		}
		wait(&status);
		if (WIFEXITED(status))
			a->status_cmd = WEXITSTATUS(status);
		return (1);
	}
	return (0);
}

void	ft_cmd_not_found(t_all *a, char *name_prg, char *cmd)
{
	a->status_cmd = 127;
	ft_printf(1, "%s: %s: %s\n", ft_strchr(name_prg, '/') + 1, cmd, strerror(2));
}



void	ft_launch_execve_path_cmd(char **arg, t_all *a
		, char *name_prg, char *cmd)
{
	char	**path_cmd;
	int		i;

	i = -1;
	path_cmd = ft_split(ft_keyshr(a->env, "PATH")->content, ':');
	while (path_cmd[++i])
	{
		if ((path_cmd[i])[ft_strlen(path_cmd[i]) - 1] != '/')
			path_cmd[i] = ft_strjoin_free(path_cmd[i], "/");
		path_cmd[i] = ft_strjoin_free(path_cmd[i], cmd);
		if (ft_launch_execve_with_path(path_cmd[i], a, arg))
		{
			ft_point_gc_on_split(&a->gc, path_cmd);
			return ;
		}
	}
	ft_point_gc_on_split(&a->gc, path_cmd);
	ft_cmd_not_found(a, name_prg, cmd);
}

void	ft_launch_execve(char *cmd, t_all *a, char *name_prg)
{
	char	**arg;

	arg = pick_argument_and_add_name_prg(a, name_prg);
	if (ft_strchr(cmd, '/'))
	{
		if (!ft_launch_execve_with_path(cmd, a, arg))
			ft_cmd_not_found(a, name_prg, cmd);
		return ;
	}
	ft_launch_execve_path_cmd(arg, a, name_prg, cmd);
}
