/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 10:27:21 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/15 15:36:28 by alafranc         ###   ########lyon.fr   */
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

void	ft_get_path(char *arg, char **path, t_all *a)
{
	int	i;

	i = 0;
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
}

int		ft_cd(t_all *a, char **arg)
{
	char	*path;
	char	*buf;
	int		ret;
	t_env	*env;

	ret = 0;
	path = 0;
	if (!arg)
		path = NULL;
	else
		ft_get_path(arg[0], &path, a);
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
		ft_no_such_file(a, "cd");
		return (1);
	}
	buf = malloc_gc(&a->gc, 200);
	buf = getcwd(buf, sizeof(char) * 200);
	env = ft_keyshr(a->env, "PWD");
	env->content = buf;
	return (ret);
}

int		ft_pwd(t_all *a, char **args)
{
	char	*buf;

	(void)args;
	buf = malloc_gc(&a->gc, sizeof(char) * 200);
	buf = getcwd(buf, 200);
	ft_printf(1, "%s\n", buf);
	return (0);
}
