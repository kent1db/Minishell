/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:34:43 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/17 13:13:12 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_all *a, char **args)
{
	int		i;
	t_env	*new_elem;

	i = -1;
	(void)new_elem;
	(void)a;
	(void)args;
	if (!args)
		return (ft_print_alphabetic_env(a->env));
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
int	ft_unset(t_all *a, char **args)
{
	int	i;

	i = -1;
	(void)a;
	(void)args;
	// if (!args)
	// 	return ;
	// while (args[++i])
	// 	ft_lst_remove_key(env, args[i]);
	return (0);
}
