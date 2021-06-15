/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_execve.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:22 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 15:44:48 by alafranc         ###   ########lyon.fr   */
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

void	ft_launch_execve_main(char **arg, t_all *a, t_command *cmd)
{
	char	**path_cmd;
	int		i;

	i = -1;
	path_cmd = ft_split(ft_keyshr(a->env, "PATH")->content, ':');
	while (path_cmd[++i])
	{
		if ((path_cmd[i])[ft_strlen(path_cmd[i]) - 1] != '/')
			path_cmd[i] = ft_strjoin_free(path_cmd[i], "/");
		path_cmd[i] = ft_strjoin_free(path_cmd[i], cmd->cmd);
		if (ft_launch_execve_with_path(path_cmd[i], a, arg))
		{
			ft_point_gc_on_split(&a->gc, path_cmd);
			return ;
		}
	}
	ft_point_gc_on_split(&a->gc, path_cmd);
	ft_cmd_not_found(a, cmd->cmd);
}

int	ft_is_a_directory(char *cmd_path)
{
	struct stat buf;
	int			ret;
	
	ret = lstat(cmd_path, &buf);
	if (!ret && S_ISDIR(buf.st_mode))
		return (1);
	return (0);
}

void	ft_launch_execve(t_command *cmd, t_all *a)
{
	char	**arg;

	arg = parse_argument(a, cmd->args);
	arg = ft_strsjoin_begin(arg, a->name_prg);
	ft_strs_add_to_gc(arg, &a->gc);
	if (ft_strchr(cmd->cmd, '/'))
	{
		if (ft_is_a_directory(cmd->cmd))
			ft_error_is_a_directory(a, cmd->cmd);
		else if (!ft_launch_execve_with_path(cmd->cmd, a, arg))
			ft_cmd_not_found(a, cmd->cmd);
		return ;
	}
	ft_launch_execve_main(arg, a, cmd);
}
