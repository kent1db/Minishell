/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:27:21 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/14 16:09:26 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_content_shr(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

void	ft_init_old_pwd(t_all *a)
{
	t_env	*env;
	int		len;
	char	*old_pwd;
	char	*pwd;

	pwd = ft_content_shr(a->env, "PWD");
	if (pwd != NULL)
	{
		old_pwd = malloc_gc(&a->gc, sizeof(char) * ft_strlen(pwd) + 1);
		ft_strcpy(old_pwd, pwd);
		env = ft_keyshr(a->env, "OLDPWD");
		if (env)
			env->content = old_pwd;
	}
}


int	ft_get_path(char *arg, char **path, t_all *a)
{
	int	i;

	i = 0;
	if (arg == NULL)
		return (0);
	while (arg && arg[i] && arg[i] != ' ')
		i++;
	*path = malloc_gc(&a->gc, sizeof(char) * i + 1);
	i = 0;
	while (arg && arg[i] && arg[i] != ' ')
	{
		(*path)[i] = arg[i];
		i++;
	}
	(*path)[i] = '\0';
	return (1);
}

int		ft_cmd_cd(char *arg, t_all *a)
{
	char	*path;
	char	*buf;
	int		ret;
	t_env	*env;

	if (!ft_get_path(arg, &path, a))
		path = NULL;
	// ft_printf(1, "path = %s\n", path);
	if (path && !ft_strncmp("-", path, 2))
	{
		if (ft_content_shr(a->env, "OLDPWD") == NULL)
			ft_printf(1, "OLDPWD not set\n");
		else
			ret = chdir(ft_content_shr(a->env, "OLDPWD"));
		ft_init_old_pwd(a);
	}
	else if (path == NULL || (!ft_strncmp("~", path, 2)))
	{
		ft_init_old_pwd(a);
		if (ft_content_shr(a->env, "HOME") != NULL)
			ret = chdir(ft_content_shr(a->env, "HOME"));
	}
	else
	{
		ft_init_old_pwd(a);
		ret = chdir(path);
	}
	if (ret == -1 && ft_strcmp(path, "-"))
	{
		ft_printf(1, "bash: cd: %s: %s\n", path, strerror(errno));
		return (ret);
	}
	buf = malloc_gc(&a->gc, 200);
	buf = getcwd(buf, sizeof(char) * 200);
	env = ft_keyshr(a->env, "PWD");
	env->content = buf;
	ft_printf(1, "ret = %d\n", ret);
	free(buf);
	return (ret);
}

void		ft_cmd_pwd(t_all *a)
{
	char	*buf;

	buf = malloc_gc(&a->gc, sizeof(char) * 200);
	buf = getcwd(buf, 200);
	ft_printf(1, "%s\n", buf);
}

int		ft_exec_command(t_all *a)
{
	char	*arg;

	arg = NULL;
	if (a->tree->type && a->tree->type == command)
	{
		if (!ft_strcmp("cd", a->tree->exec->cmd->cmd))
		{
			if (a->tree->exec->cmd->args)
				arg = a->tree->exec->cmd->args;
			ft_cmd_cd(arg, a);
		}
		if (!(ft_strcmp("pwd", a->tree->exec->cmd->cmd)))
			ft_cmd_pwd(a);
	}
	return (0);
}