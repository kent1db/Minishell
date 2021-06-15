/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 15:46:45 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 16:33:24 by alafranc         ###   ########lyon.fr   */
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

int	count_split_quote(char *str, char del)
{
	int		i;
	int		r;
	int		count;
	t_list	*arg;

	arg = NULL;
	i = 0;
	count = 0;
	while (str[i])
	{
		while (ft_is_backslash_before(str, i, del) && str[i])
			i++;
		r = i;	
		while (!ft_is_backslash_before(str, i, del) && str[i])
		{
			if (ft_is_backslash_before(str, i, '\''))
				jump_to_next_quote(&i, str, str[i]);
			else
				i++;
		}
		count++;
	}
	return (count);
}


char	**ft_split_quote(char *str, char del)
{
	int		i;
	int		j;
	int		r;
	char	**arg;

	if (!str)
		return (NULL);
	arg = malloc(sizeof(char *) * (count_split_quote(str, del) + 1));
	i = 0;
	j = -1;
	while (str[i])
	{
		while (ft_is_backslash_before(str, i, del) && str[i])
			i++;
		r = i;	
		while (!ft_is_backslash_before(str, i, del) && str[i])
		{
			if (ft_is_backslash_before(str, i, '\''))
				jump_to_next_quote(&i, str, str[i]);
			else
				i++;
		}
		arg[++j] = ft_substr(str, r, i - r);
	}
	arg[++j] = NULL;
	return (arg);
}
