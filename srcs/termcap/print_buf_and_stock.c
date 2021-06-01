/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buf_and_stock.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 18:08:36 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/01 18:26:07 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_print_buf(char *str, int *cursor)
{
	int	size_print;
	int	i;

	if (!str)
		return (0);
	i = -1;
	size_print = 0;
	while (str[++i])
		size_print += ft_printf(1, "%c", str[i]);
	if (size_print == 0)
		return (0);
	*cursor += size_print;
	return (1);
}

void	ft_print_buf_and_stock(t_all *a, char **line, char *buf, int *cursor)
{
	int	size_print;

	if (ft_print_buf(buf, cursor))
	{	
		if (!line || !(*line))
			*line = ft_strdup_gc(&a->gc, buf);
		else if (ft_strlen(*line) == (size_t)(*cursor))
			*line = ft_strjoin(*line, buf);
		else
			*line = ft_add_string_in_index(a->gc, *line, buf, *cursor);
		a->termcap->historic_current = ft_lstnew(*line);
		ft_lstadd_front(&a->gc, a->termcap->historic_current);
	}
}