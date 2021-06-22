/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:34:43 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/22 15:25:58 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_all *a, char **args)
{
	int		i;
	t_env	*new_elem;

	i = -1;
	(void)new_elem;
	if (!args)
		return (ft_print_alphabetic_env(a->env));
	while (args[++i])
	{
		if (ft_strchr(args[i], '='))
		{
			new_elem = pick_key_and_content(args[i], &a->gc, 1);
			if (new_elem)
				dprintf(1, "%s, %s\n", new_elem->key, new_elem->content);
			if (ft_keyshr(a->env, new_elem->key))
			{
				dprintf(1, "je supprime l'ancien\n");
				ft_lst_remove_key(&(a->env), new_elem->key);
			}
			ft_lstadd_back_env(&a->env, new_elem);
			ft_lstadd_front(&a->gc, ft_lstnew(new_elem));
		}
		else
		{
			new_elem = ft_keyshr(a->env, args[i]);
			if (new_elem)
				new_elem->status = status_env;
		}
	}
	return (0);
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
