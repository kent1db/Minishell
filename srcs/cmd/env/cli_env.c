/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cli_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:45:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/27 09:55:08 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_all *a)
{
	while (a->env)
	{
		if (a->env->status == status_env)
			ft_printf(1, "%s=%s\n", a->env->key, a->env->content);
		a->env = a->env->next;
	}
	return (0);
}

// A DECOMMENTER QUAND ON AURA LES ARGUMENTS DANS LA STRUCT A
int	ft_export(t_all *a)
{
	int		i;
	t_env	*new_elem;

	i = -1;
	// if (!args)
	// 	return ;
	// while (args[++i])
	// {
	// 	if (ft_strchr(args[i], '='))
	// 	{
	// 		new_elem = pick_key_and_content(args[i], gc, 1);
	// 		if (ft_keyshr(*env, new_elem->key))
	// 			ft_lst_remove_key(env, new_elem->key);
	// 		ft_lstadd_back_env(env, new_elem);
	// 		ft_lstadd_front(gc, ft_lstnew(new_elem));
	// 	}
	// 	else
	// 	{
	// 		new_elem = ft_keyshr(*env, args[i]);
	// 		if (new_elem)
	// 			new_elem->status = status_env;			
	// 	}
	// }
	return (0);
}

// A DECOMMENTER QUAND ON AURA LES ARGUMENTS DANS LA STRUCT A
int	ft_unset(t_all *a)
{
	int	i;

	i = -1;
	// if (!args)
	// 	return ;
	// while (args[++i])
	// 	ft_lst_remove_key(env, args[i]);
	return (0);
}
