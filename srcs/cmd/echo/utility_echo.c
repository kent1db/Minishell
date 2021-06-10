/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 14:22:33 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/10 14:23:02 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_reverse_boolean(int boolean)
{
	if (boolean)
		return (0);
	return (1);
}

int	ft_ccmp(char c, char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (1);
	}
	return (0);
}

int	is_option(char *args, t_all *a)
{
	int	i;

	if (!args)
		return (0);
	i = 0;
	args = delete_quote(args);
	ft_lstadd_front(&a->gc, ft_lstnew(args));
	while (args[i])
	{
		if (args[i++] == '-')
		{
			while (args[i] == 'n' && args[i])
				i++;
			if (args[i])
				return (0);
			else
				return (1);
		}
	}
	return (0);
}

t_env  	*find_env(t_all *a, char *arg,  int *i)
{
	char	*str_env;
	t_env	*find_env;
	int		r;

	r = *i;
	if (ft_ccmp(arg[*i], "0123456789?"))	
		str_env = ft_substr(arg, (*i)++, 1);
	else
		while (arg[*i] && !ft_ccmp(arg[*i], " =\\?") && !is_quote_or_d_quote(arg, *i)
				&& !is_char_whitout_backslash(arg, *i, '$'))
			(*i)++;
	str_env = ft_substr(arg, r, *i - r);
	ft_lstadd_front(&a->gc, ft_lstnew(str_env));
	find_env = ft_keyshr(a->env, str_env);
	return (find_env);
}
