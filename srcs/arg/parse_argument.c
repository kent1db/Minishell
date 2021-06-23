/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 13:04:12 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/23 11:37:19 by alafranc         ###   ########lyon.fr   */
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
		while (arg[*i] && !ft_ccmp(arg[*i], " =+-\\?") && !is_quote_or_d_quote(arg, *i)
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

int		ft_count_remove_null(char **strs, int size_arg)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (!strs)
		return (0);
	while (i != size_arg)
		if (strs[i++])
			count++;
	return (count);
}
char	**ft_remove_null(char **strs, int size_arg)
{
	int	i;
	int	j;
	char **new_strs;

	i = 0;
	j = -1;
	if (!strs)
		return (NULL);
	new_strs = malloc(sizeof(char *) * (ft_count_remove_null(strs, size_arg) + 1));
	while (i != size_arg)
	{
		if (strs[i])
			new_strs[++j] = ft_strdup(strs[i]);
		i++;
	}
	new_strs[++j] = NULL;
	return (new_strs);
}

char	**parse_argument(t_all *a, char *args)
{
	char	**arg_split;
	int		i;
	int		size_arg;

	arg_split = ft_split_quote(args, ' ');
	size_arg = ft_strslen(arg_split);
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
	i = 0;
	arg_split = ft_remove_null(arg_split, size_arg);
	ft_strs_add_to_gc(arg_split, &a->gc);
	return (arg_split);
}
