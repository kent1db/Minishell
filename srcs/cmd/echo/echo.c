/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/09 15:55:52 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*transform_arg_with_env(char *arg, t_all *a)
{
	int		i;
	char	quote;
	t_env	*str_env;
	char	*new_str;
	char	buf[2];

	i = 0;
	quote = 0;
	new_str = NULL;
	while (arg[i])
	{
		if ((arg[i] == '\'' || arg[i] == '\"') && quote == 0)
			quote = arg[i];
		else if (arg[i] == quote)
			quote = 0;
		if (arg[i] == '~')
		{
			i++;
			str_env = ft_keyshr(a->env, "HOME");
			if (str_env && str_env->content)
			{
				new_str = ft_strjoin(new_str, str_env->content);
				ft_lstadd_front(&a->gc, ft_lstnew(new_str));
			}
		}
		else if (arg[i] == '$' && quote != '\'' && arg[i + 1] && arg[i + 1] != ' ')
		{
			i++;
			str_env = find_env(a, arg, &i);
			if (str_env && str_env->content)
			{
				new_str = ft_strjoin(new_str, str_env->content); 
				ft_lstadd_front(&a->gc, ft_lstnew(new_str));
			}			
			
		}
		else
		{
			buf[0] = arg[i];
			buf[1] = '\0';
			new_str = ft_strjoin(new_str, buf);
			ft_lstadd_front(&a->gc, ft_lstnew(new_str));
			i++;
		}
	}
	return (new_str);
}

void	delete_option_and_empty_quote(t_list **arg_split, t_all *a, int *option)
{
	t_list *current;

	current = *arg_split;
	while (current)
	{
		current->content = delete_empty_quote(current->content);
		ft_lstadd_front(&a->gc, ft_lstnew(current->content));
		current->content = transform_arg_with_env(current->content, a);
		ft_lstadd_front(&a->gc, ft_lstnew(current->content));
		if (is_option(current->content, a))
		{
			*option = 1;
			ft_lst_remove_if(arg_split, current);
		}
		current = current->next;
	}
}

void	main_echo(t_list **arg_split,  t_all *a)
{
	t_list *current;

	current = *arg_split;
	while (current)
	{	
		ft_lstadd_front(&a->gc, ft_lstnew(current->content));
		if (current->content)
			ft_printf(1, "%s", current->content);
		current = current->next;
		if (current)
			ft_printf(1, " ");
	}
}

int	ft_echo(t_all *a, char *args)
{
	int		option;
	t_list	*arg_split;

	if (!args)
		return (0);
	arg_split = ft_split_quote(args, ' ');
	option = 0;
	ft_lst_add_to_gc(&a->gc, arg_split);
	delete_option_and_empty_quote(&arg_split, a, &option);
	main_echo(&arg_split, a);
	if (!option)
		ft_printf(1, "\n");
	return (0);
}
