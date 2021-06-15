/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backslash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/10 13:01:18 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/10 14:29:30 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_delete_backslash(char *str)
{
	int	i;
	int	count;
	int	quote;

	if (!str)
		return (0);
	i = 0;
	count = 0;
	quote = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quote = 1;
		if (str[i] == '\\' && !quote && str[i + 1])
		{
			count++;
			i += 2;
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

char	*delete_backslash(char *str)
{
	int		i;
	int		j;
	char	*new_str;
	int		quote;

	if (!str)
		return (str);
	i = 0;
	j = -1;
	quote = 0;
	new_str = malloc(sizeof(char) * (count_delete_backslash(str) + 1));
	while (str[i])
	{
		if (str[i] == '\'')
			quote = 1;
		if (str[i] == '\\' && !quote && str[i + 1])
		{
			new_str[++j] = str[i + 1];
			i += 2;
		}
		else
		{
			new_str[++j] = str[i];
			i++;
		}
	}
	new_str[++j] = '\0';
	return (new_str);
}