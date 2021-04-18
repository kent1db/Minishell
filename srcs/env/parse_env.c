/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:15:54 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/18 17:56:59 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*pick_key_and_content(char *envp, t_list **gc)
{
	char	*key;
	char	*content;
	int		i;

	i = ft_strchr_index(envp, '=');
	if (i == -1)
		return (NULL);
	key = ft_substr(envp, 0, i);
	ft_lstadd_front(gc, ft_lstnew(key));
	content = ft_strdup(&envp[i + 1]);
	ft_lstadd_front(gc, ft_lstnew(content));
	if (!key || !content)
		ft_error_msg("Malloc error", *gc);
	return (ft_lstnew_env(key, content, 1));
}

t_env	*parse_env(char **envp, t_list **gc)
{
	t_env	*env;
	t_env	*new_elem;

	env = NULL;
	while (*envp)
	{
		new_elem = pick_key_and_content(*envp, gc);
		if (!new_elem)
			ft_error_msg("Malloc error", *gc);
		ft_lstadd_back_env(&env, new_elem);
		ft_lstadd_front(gc, ft_lstnew(new_elem));
		envp++;
	}
	return (env);
}