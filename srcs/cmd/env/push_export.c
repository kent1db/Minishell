/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:58:33 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/22 16:39:02 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_variable(char *str, t_all *a, t_status status)
{
	t_env	*new_elem;

	new_elem = pick_key_and_content(str, &a->gc, status);
	if (ft_keyshr(a->env, new_elem->key))
		ft_lst_remove_key(&(a->env), new_elem->key);
	ft_lstadd_back_env(&a->env, new_elem);
	ft_lstadd_front(&a->gc, ft_lstnew(new_elem));
}


void	push_variable_whitout_export(t_command *cmd, t_all *a)
{
	int	i;

	i = -1;
	push_variable(cmd->cmd, a, status_none);
	if (cmd->handle_arg)
		while(cmd->handle_arg[++i])
			push_variable(cmd->handle_arg[i], a, status_none);
}