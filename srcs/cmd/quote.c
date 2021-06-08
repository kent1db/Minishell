/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 12:07:32 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/08 15:59:46 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_delete_empty_quote(char *str)
{
	int	i;
	int	count;

	count = 1;
	i = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '\"' && str[i + 1] == '\"'))
			i += 2;
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	count_whitout_quote(char *args)
{
	int		count;
	int		i;
	char	quote;

	if (!args)
		return (0);
	count = 0;
	i = -1;
	while (args[++i])
	{
		if (quote == args[i])
			quote = 0;
		else if ((args[i] == '\'' && quote != '\"')
				|| (args[i] == '\"' && quote != '\''))
			quote = args[i];
		else
			count++;
	}
	return (count);
}

char	*delete_quote(char *args)
{
	int		i;
	int		j;
	char	quote;
	char	*new_args;

	if (!args)
		return (NULL);
	i = -1;
	j = -1;
	quote = 0;
	new_args = malloc(sizeof(char) * (count_whitout_quote(args) + 1));
	while (args[++i])
	{
		if (quote == args[i])
			quote = 0;
		else if ((args[i] == '\'' && quote != '\"')
				|| (args[i] == '\"' && quote != '\''))
			quote = args[i];
		else
			new_args[++j] = args[i];
	}
	new_args[++j] = '\0';
	return (new_args);
}

char	*delete_empty_quote(char *str)
{
	int	i;
	int	j;
	char	*new_str;

	new_str = malloc(sizeof(char) * (count_delete_empty_quote(str) + 1));
	i = 0;
	j = 0;
	while (str[i] && str[i + 1])
	{
		if ((str[i] == '\'' && str[i + 1] == '\'') || (str[i] == '\"' && str[i + 1] == '\"'))
			i += 2;
		else
		{
			new_str[j++] = str[i];
			i++;
		}
	}
	new_str[j++] = str[i];
	new_str[j++] = '\0';
	return (new_str);
}