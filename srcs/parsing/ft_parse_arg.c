/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_arg.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:19 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/20 16:00:27 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ft_skip_whitespace(char *line, int *i)
// {
// 	while (line[*i] && line[*i] == ' ')
// 		(*i)++;
// }

// int	ft_is_delimiteur(char c)
// {
// 	char	*op;
// 	int		i;

// 	i = -1;
// 	op = " ;><|\t";
// 	while (op[++i])
// 	{
// 		if (op[i] == c)
// 			return (1);
// 	}
// 	if (c == '\0')
// 		return(1) ;
// 	return (0);
// }

void	ft_lexing_command_line(char *line, t_list **gc)
{
	// int	i;
	// int	count;

	// i = -1;
	// count = 0;
	// while (line[++i])
	// {
	// 	ft_skip_whitespace(line, &i);
	// 	while (!ft_is_delimiter(line[i++]))
	// 		count++;
	// 	ft_skip_whitespace(line, &i);
	// }
	// ft_printf(1, "count = %d\n");
}
