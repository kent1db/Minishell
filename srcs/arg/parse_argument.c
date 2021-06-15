/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:04:12 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 16:33:24 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				&& !ft_is_backslash_before(arg, *i, '$'))
			(*i)++;
	str_env = ft_substr(arg, r, *i - r);
	ft_lstadd_front(&a->gc, ft_lstnew(str_env));
	find_env = ft_keyshr(a->env, str_env);
	return (find_env);
}

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
		if (ft_is_backslash_before(arg, i, '~'))
		{
			i++;
			str_env = ft_keyshr(a->env, "HOME");
			if (str_env && str_env->content)
			{
				new_str = ft_strjoin(new_str, str_env->content);
				ft_lstadd_front(&a->gc, ft_lstnew(new_str));
			}
		}
		else if (ft_is_backslash_before(arg, i, '$') && quote != '\'' && arg[i + 1] && !ft_ccmp(arg[i + 1], "= $\'\""))
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

char	**parse_argument(t_all *a, char *args)
{
	char	**arg_split;
	int		i;

	arg_split = ft_split_quote(args, ' ');
	ft_strs_add_to_gc(arg_split, &a->gc);
	i = -1;
	while (arg_split && arg_split[++i])
	{
		arg_split[i] = transform_arg_with_env(arg_split[i], a);
		arg_split[i] = delete_empty_quote(&a->gc, arg_split[i]);
		arg_split[i] = add_backslash_quote(&a->gc, arg_split[i]);
		arg_split[i] = delete_quote(&a->gc, arg_split[i]);
		arg_split[i] = delete_backslash(&a->gc, arg_split[i]);
	}
	return (arg_split);
}
