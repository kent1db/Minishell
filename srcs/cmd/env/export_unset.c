/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:34:43 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/23 16:44:03 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env *duplicate_env(t_env *env)
{
	t_env *new_env;

	new_env = NULL;
	while (env)
	{
		ft_lstadd_back_env(&new_env, ft_lstnew_env(env->key, env->content, env->status));
		env = env->next;
	}
	return (new_env);
}

int	ft_export(t_all *a, char **args)
{
	int		i;
	t_env	*new_elem;
	char	*chr;

	i = -1;
	if (!args)
		return (ft_print_alphabetic_env(duplicate_env(a->env)));
	while (args[++i])
	{
		if ((chr = ft_strchr(args[i], '+')) && chr && chr[1] == '=')
			push_variable(args[i], a, status_env, 1);
		else if (ft_strchr(args[i], '='))
			push_variable(args[i], a, status_env, 0);
		else
		{
			new_elem = ft_keyshr(a->env, args[i]);
			if (new_elem)
				new_elem->status = status_env;
			else
				push_variable(args[i], a, status_export, 0);
		}
	}
	return (a->status);
}

int	ft_unset(t_all *a, char **args)
{
	int	i;

	i = -1;
	if (!args)
		return (0);
	while (args[++i])
		ft_lst_remove_key(&a->env, args[i]);
	return (0);
}
