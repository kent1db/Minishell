/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:46:45 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/08 13:12:07 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	jump_to_next_quote(int *i, char *str, char quote)
{
	(*i)++;
	while (str[*i] != quote && str[*i])
		(*i)++;
	if (str[*i])
		(*i)++;
}

t_list	*ft_split_quote(char *str, char del)
{
	int		i;
	int		r;
	t_list	*arg;

	arg = NULL;
	i = 0;
	while (str[i])
	{
		while (str[i] == del && str[i])
			i++;
		r = i;	
		while (str[i] != del && str[i])
		{
			if (str[i] == '\'' || str[i] == '\"')
				jump_to_next_quote(&i, str, str[i]);
			else
				i++;
		}
		ft_lstadd_back(&arg, ft_lstnew(ft_substr(str, r, i - r)));
	}
	return (arg);
}
