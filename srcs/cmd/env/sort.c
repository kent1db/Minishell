/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:34:28 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/16 17:01:50 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_switch_link_begin(t_env **begin)
{
	t_env **second;

	second = malloc(sizeof(t_env));
	*second = (*begin)->next;
	(*begin)->next = (*second)->next;
	(*second)->next = (*begin);
	(*begin) = *second;
}

void	ft_switch_link(t_env **previous, t_env **current, t_env **next)
{

	t_env *tmp;

	tmp = (*previous);
	(*previous) = (*current);
	(*current) = (*next);
	(*next) = tmp;
}

void    ft_print_env(t_env *env)
{
	while (env)
	{
		if (env->status == status_env)
			ft_printf(1, "%s=%s\n", env->key, env->content);
		env = env->next;
	}
}

t_env *ft_sort_alphabetic_env(t_all *a, t_env *env)
{
	t_env *current;
	t_env *previous;
	t_env *begin;

	previous = NULL;
	current = env;
	begin = env;
	ft_print_env(env);
	ft_printf(1, "\n\n");
	while (current && current->next)
	{
		if (ft_strcmp(current->key, current->next->key) > 0)
		{
			if (previous)
				ft_switch_link(&previous->next, &current->next, &current->next->next);
			else
				ft_switch_link_begin(&begin);
			previous = NULL;
			current = begin;
		}
		else
		{
			previous = current;	
			current = current->next;
		}
	}
	return (begin);
}

int	ft_print_alphabetic_env(t_all *a, t_env *env)
{
	env = ft_sort_alphabetic_env(a, env);
	// ft_env(a, NULL);
	ft_print_env(env);
	return (0);
}