/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 13:58:33 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/24 11:33:18 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg_export(char *error)
{
	ft_printf(2, "minichiale: `%s': not a valid identifier\n", error);
}

int	is_only_equal(char *str)
{
	int	i;

	i = 0;
	(void)str;
	if (!str)
		return (1);
	while (str[i] == '=' && str[i])
		i++;
	if (!str[i])
		return (1);
	return (0);
}

int	ft_strchr_str(char *str, char *find)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		j = 0;
		while (find[j])
		{
			if (str[i] == find[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}


int	check_error_export(char *str, t_env *new_elem)
{
	if (new_elem && new_elem->key && ft_isdigit(new_elem->key[0]))
		error_msg_export(str);
	else if (new_elem && !new_elem->key)
		error_msg_export(str);
	else if (new_elem && (new_elem->content && is_only_equal(new_elem->content)))
		error_msg_export(str);
	else if (new_elem && (new_elem->key && is_only_equal(new_elem->key)))
		error_msg_export(str);
	else if (new_elem && ft_strchr_str(new_elem->key, "+\\.$.+}{-*#@!^~"))
		error_msg_export(str);
	else
		return (0);
	return (1);
}

int	push_variable(char *str, t_all *a, t_status status, int is_join)
{
	t_env	*new_elem;
	t_env	*env;

	if (is_join)
		new_elem = pick_key_and_content(str, &a->gc, status, '+');
	else
		new_elem = pick_key_and_content(str, &a->gc, status, '=');
	if (check_error_export(str, new_elem))
	{
		a->status = 1;
		return (0);		
	}
	if (new_elem)
		env = ft_keyshr(a->env, new_elem->key);
	else
		env = NULL;
	if (new_elem && env)
	{
		if (is_join)
			env->content = ft_strjoin(env->content, new_elem->content);
		else
			ft_lst_remove_key(&(a->env), new_elem->key);
	}
	else if (new_elem)
	{
		ft_lstadd_back_env(&a->env, new_elem);
		ft_lstadd_front(&a->gc, ft_lstnew(new_elem));
	}
	return (1);
}


void	push_variable_whitout_export(t_command *cmd, t_all *a)
{
	int	i;

	i = -1;
	push_variable(cmd->cmd, a, status_none, 0);
	if (cmd->handle_arg)
		while(cmd->handle_arg[++i])
			push_variable(cmd->handle_arg[i], a, status_none, 0);
}