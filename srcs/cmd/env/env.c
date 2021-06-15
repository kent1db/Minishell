/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 14:45:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 17:25:06 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_all *a, char **args)
{
	(void)args;
	t_env *begin_env;

	begin_env = a->env;
	while (a->env)
	{
		if (a->env->status == status_env)
			ft_printf(1, "%s=%s\n", a->env->key, a->env->content);
		a->env = a->env->next;
	}
	a->env = begin_env;
	return (0);
}


void	ft_switch_link(t_env **env, t_env **previous, t_env **env1, t_env **env2)
{
	if (*previous)
		ft_printf(1, "prev: %s\n", (*previous)->content);
		// (*previous)->next = *env2;
	// else
		// *env = (*env2)->next;
	// if (*env1 && *env2)
	if (*env1)
		ft_printf(1, "1: %s\n", (*env1)->content);
		// (*env1)->next = (*env2)->next;
	// else if (*env1 && !*env2)
		// (*env1)->next = NULL;
	// if (*env2)
		(*env2)->next = (*env1);
		// ft_printf(1, "2: %s\n", (*env2)->content);
		// (*env2)->next = *env1;
}

t_env *ft_sort_alphabetic_env(t_all *a, t_env *env)
{
	t_env *current;
	t_env *previous;

	current = env;
	previous = NULL;
	while (current && current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			ft_printf(1, "switch\n");
			ft_switch_link(&env, &previous, &current, &(current->next));
			ft_env(a, NULL);
			sleep(-1);

			current = env;
			previous = NULL;
		}
		previous = current;	
		current = current->next;
	}
	return (env);
}

int	ft_print_alphabetic_env(t_all *a, t_env *env)
{
	env = ft_sort_alphabetic_env(a, env);
	ft_env(a, NULL);
	return (0);
}

// A DECOMMENTER QUAND ON AURA LES ARGUMENTS DANS LA STRUCT A
int	ft_export(t_all *a, char **args)
{
	int		i;
	t_env	*new_elem;

	i = -1;
	(void)new_elem;
	(void)a;
	(void)args;
	if (!args)
		return (ft_print_alphabetic_env(a, a->env));
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
