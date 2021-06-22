/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:22 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/22 15:40:14 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_our_cmd(t_command *cmd, t_all *a, char **cmd_done)
{
	int		i;
	char	**args;

	i = -1;
	args = parse_argument(a, cmd->args);
	while (cmd_done[++i])
		if (!ft_strcmp(cmd->cmd, cmd_done[i]))
			return (i);
	return (0);
}

void	ft_exec_cmd_main(t_command *cmd, t_all *a)
{
	int		status;
	pid_t	pid;
	int		(**ft_cmd)(t_all *a, char **args);

	if (cmd->error)
	{
		if (cmd->error == 127)
			ft_cmd_not_found(a, cmd->cmd);
		if (cmd->error == 126)
			ft_error_is_a_directory(a, cmd->cmd);
		return ;
	}
	if (cmd->our_cmd != -1 && !a->pipe->is_pipe)
	{
		ft_cmd = init_array_instruction_function(&a->gc);
		ft_cmd[cmd->our_cmd](a, cmd->handle_arg);
	}
	else
	{
		if (pipe(a->pipe->fd) == -1)
			ft_error_msg("PIPE INIT", a->gc);
		pid = fork();
		if (pid == 0)
		{
			if (a->pipe->is_pipe)
			{
				dup2(a->pipe->backup_tmp, 0);
				if (a->pipe->count != 0)
					dup2(a->pipe->fd[1], 1);
				close(a->pipe->fd[0]);
			}
		if (cmd->our_cmd != -1)
		{
			ft_cmd = init_array_instruction_function(&a->gc);
			ft_cmd[cmd->our_cmd](a, cmd->handle_arg);
		}
			else
				execve(cmd->cmd, cmd->handle_arg, convert_env_to_strs(&a->gc, a->env));
			exit(0);
		}
		a->pipe->count -= 1;
		close(a->pipe->fd[1]);
		a->pipe->backup_tmp = a->pipe->fd[0];
		wait(&status);
		a->status = WEXITSTATUS(status);
	}
}

void	ft_status_cmd(t_all *a, int *status_cmd)
{
	t_env	*env;

	env = ft_keyshr(a->env, "?");
	if (!env)
		return ;
	env->content = ft_itoa(*status_cmd);
	ft_lstadd_front(&a->gc, ft_lstnew(env->content));
	*status_cmd = 0;
}

void	ft_exec_cmd(t_command *cmd, t_all *a)
{
	char	**cmd_done;

	if (!cmd || !cmd->cmd)
		return ;
	a->in_cmd = 1;
	cmd->cmd = parse_argument(a, cmd->cmd)[0];
	cmd->handle_arg = parse_argument(a, cmd->args);
	cmd->error = 0;
	cmd_done = list_cmd_done(&a->gc);
	cmd->our_cmd = ft_is_our_cmd(cmd, a, cmd_done);
	if (cmd->our_cmd == -1)
		fill_cmd_with_path(cmd, a);
	ft_exec_cmd_main(cmd, a);
	a->in_cmd = 0;
	ft_status_cmd(a, &a->status);
	if (a->redir->fd != -1)
	{
		
	}
		reset_redir(a->redir);
}
