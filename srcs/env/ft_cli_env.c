/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cli_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 17:19:03 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/19 17:35:28 by alafranc         ###   ########lyon.fr   */
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

void	ft_export(t_env **env, char **args, t_list **gc)
{
	int	i;
	t_env *new_elem;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			new_elem = pick_key_and_content(args[i], gc, 1);
			if (ft_keyshr(*env, new_elem->key))
				ft_lst_remove_key(env, new_elem->key);
			ft_lstadd_back_env(env, new_elem);
			ft_lstadd_front(gc, ft_lstnew(new_elem));				
		}
		else
		{
			new_elem = ft_keyshr(*env, args[i]);
			if (new_elem)
				new_elem->is_push = 1;			
		}
	}
}

void	ft_unset(t_env **env, char **args)
{
	int	i;

	i = -1;
	if (!args)
		return ;
	while (args[++i])
		ft_lst_remove_key(env, args[i]);
}