/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 11:56:26 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/08 15:52:06 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reverse_boolean(int boolean)
{
	if (boolean)
		return (0);
	return (1);
}

int	is_option(char *args)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	args = delete_quote(args);
	while (args[i])
	{
		if (args[i++] == '-')
		{
			while (args[i] == 'n' && args[i])
				i++;
			if (!args[i])
				return (1);
		}
	}
	return (0);
}

char	*find_env(t_all *a, char *arg,  int *i, int quote)
{
	char	*str_env;
	t_env	*find_env;
	int		r;

	r = *i;
	while (!quote && arg[*i] && arg[*i] != ' ' && 
			arg[*i] != '\'' && arg[*i] != '\"')
		(*i)++;
	str_env = ft_substr(arg, r + 1, *i - r - 1);
	find_env = ft_keyshr(a->env, str_env);
	// ft_printf(1, "str_env: %s\n", str_env);
	if (!find_env)
	{
		*i = r;
		return (NULL);
	}
	return (find_env->content);
}

char	*transform_env(char *arg, t_all *a)
{
	int		i;
	int		quote;
	char	*str_env;
	char	*new_str;
	char	buf[2];

	i = 0;
	quote = 0;
	new_str = NULL;
	while (arg[i])
	{
		if (arg[i] == '\'')
			quote = ft_reverse_boolean(quote);
		else if (arg[i] == '$' && (str_env = find_env(a, arg, &i, quote)))
			new_str = ft_strjoin(new_str, str_env);
		if (arg[i])
		{
			buf[0] = arg[i];
			buf[1] = '\0';
			new_str = ft_strjoin(new_str, buf);
			i++;
		}
	}
	// ft_printf(1, "new_str: %s\n", new_str);
	return (new_str);
}

void	main_echo(t_list **arg_split, int *option, t_all *a)
{
	t_list *current;

	*option = 0;
	current = *arg_split;
	while (current)
	{	
		current->content = delete_empty_quote(current->content);
		if (is_option(current->content))
			*option = 1;
		else
		{
			current->content = transform_env(current->content, a);
			ft_printf(1, "%s", delete_quote(current->content));
		}
		current = current->next;
		if (current)
			ft_printf(1, "\n");
	}
}

int	ft_echo(t_all *a, char *args)
{
	int		option;
	t_list	*arg_split;

	if (!args)
		return (0);
	arg_split = ft_split_quote(args, ' ');
	main_echo(&arg_split, &option, a);
	// ft_lstadd_front(&a->gc, ft_lstnew(args));
	if (!option)
		ft_printf(1, "\n");
	return (0);
}
