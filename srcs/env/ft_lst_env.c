/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 18:08:50 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/17 18:19:06 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *key, char *content)
{
	t_env	*elem;

	elem = malloc(sizeof(t_env));
	if (!elem)
		return (NULL);
	elem->key = key;
	elem->content = content;
	elem->next = NULL;
	return (elem);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	if (lst == NULL)
		return (lst);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **alst, t_env *new)
{
	t_env	*last;

	last = ft_lstlast_env(*alst);
	if (last != NULL)
		last->next = new;
	else
		*alst = new;
}
