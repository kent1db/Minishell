/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cli_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:19:03 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/18 20:42:17 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->is_push)
			ft_printf("%s=%s\n", env->key, env->content);
		env = env->next;
	}
}

void	ft_export(t_env **env, char **args)
{
	
}

void	ft_unset(t_env **env, char **args)
{
	int i;

	i = -1;
	while (args[++i])
		ft_lst_remove_key(env, args[i]);
}