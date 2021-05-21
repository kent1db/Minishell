	/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:22 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/20 14:01:49 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	launch_if_is_our_cmd(char *cmd, t_all *a, char **cmd_done, int	(**ft_cmd)(t_all *a))
{
	int	i;

	i = -1;
	while (cmd_done[++i])
	{
		if (!ft_strcmp(cmd, cmd_done[i]))
		{
			if (ft_cmd[i] != NULL)
				a->error = ft_cmd[i](a);
			else
				ft_printf(1, "not done yet\n");
			return (1);
		}
	}
	return (0);
}

char	**pick_argument_and_add_name_prg(t_all *a, char *name_prg)
{
	char	**arg;

	arg = malloc_gc(&a->gc, sizeof(char *) * 2);
	arg[0] = name_prg;
	arg[1] = NULL;
	return (arg);
}

void	ft_point_on_split(t_list **gc, char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		ft_lstadd_front(gc, ft_lstnew(split[i]));
	ft_lstadd_front(gc, ft_lstnew(split));
}

// IMPROVE ./ because it works with => ./ls alors que normalement ERROR
void	ft_launch_execve(char *cmd, t_all *a, char *name_prg)
{
	char	**arg;
	char	**path_cmd;
	int		i;
	struct	stat buf;
	int			status;

	i = -1;
	path_cmd = ft_split(ft_keyshr(a->env, "PATH")->content, ':');
	path_cmd = ft_strsjoin_free(path_cmd, "./");
	arg = pick_argument_and_add_name_prg(a, name_prg);
	while (path_cmd[++i])
	{
		if (path_cmd[i][ft_strlen(path_cmd[i]) - 1] != '/')
			path_cmd[i] = ft_strjoin_free(path_cmd[i], "/");
		path_cmd[i] = ft_strjoin_free(path_cmd[i], cmd);
		if (lstat(path_cmd[i], &buf) == 0)
		{
			if (fork() == 0)
				execve(path_cmd[i], arg, NULL);
			wait(&status);
			if (WIFEXITED(status))
				a->error = WEXITSTATUS(status);
			ft_point_on_split(&a->gc, path_cmd);
			return ;
		}
	}
	ft_point_on_split(&a->gc, path_cmd);
	a->error = cmd_not_found;
}

void ft_launch_cmd(char *cmd, t_all *a, char *name_prg)
{
	char	**cmd_done;
	int	(**ft_cmd)(t_all *a);

	if (!cmd)
		return ;
	cmd_done = list_cmd_done(&a->gc);
	ft_cmd = init_array_instruction_function(&a->gc);
	if (!launch_if_is_our_cmd(cmd, a, cmd_done, ft_cmd))
		ft_launch_execve(cmd, a, name_prg);
}