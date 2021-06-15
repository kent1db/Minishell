/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 12:44:14 by alafranc         ###   ########lyon.fr   */
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
		if ((is_quote_or_d_quote(arg, i)) && quote == 0)
			quote = arg[i];
		else if (arg[i] == quote)
			quote = 0;
		if (is_char_whitout_backslash(arg, i, '~'))
		{
			i++;
			str_env = ft_keyshr(a->env, "HOME");
			if (str_env && str_env->content)
			{
				new_str = ft_strjoin(new_str, str_env->content);
				ft_lstadd_front(&a->gc, ft_lstnew(new_str));
			}
		}
		else if (is_char_whitout_backslash(arg, i, '$') && quote != '\'' && arg[i + 1] && !ft_ccmp(arg[i + 1], "= $\'\""))
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

void	transform_string_with_quote_arg_slash_env(t_list **arg_split, t_all *a, int *option)
{
	t_list *current;

	current = *arg_split;
	while (current)
	{
		current->content = transform_arg_with_env(current->content, a);
		current->content = delete_empty_quote(current->content);
		ft_lstadd_front(&a->gc, ft_lstnew(current->content));
		if (is_option(current->content, a))
		{
			*option = 1;
			ft_lst_remove_if(arg_split, current);
		}
		else
		{
			current->content = delete_quote(current->content);
			ft_lstadd_front(&a->gc, ft_lstnew(current->content));
			current->content = delete_backslash(current->content);
			ft_lstadd_front(&a->gc, ft_lstnew(current->content));
		}
		current = current->next;
	}
}

int		is_a_next(t_list *lst)
{
	while (lst)
	{
		if (lst->content)
			return (1);
		lst = lst->next;
	}
	return (0);
}

void	main_echo(t_list **arg_split)
{
	t_list *current;

	current = *arg_split;
	while (current)
	{	
		if (current->content)
		{
			ft_printf(1, "%s", current->content);
			if (is_a_next(current))
				ft_printf(1, " ");
		}
		current = current->next;
		
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
	transform_string_with_quote_arg_slash_env(&arg_split, a, &option);
	main_echo(&arg_split);
	if (!option)
		ft_printf(1, "\n");
	return (0);
}
