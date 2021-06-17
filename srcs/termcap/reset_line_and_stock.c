/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:39:20 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/17 11:02:29 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	stock_to_historic(t_all *a, char *line)
{
	t_list  *new_historic;

	if (line && line[0] != '\0')
	{
		new_historic = ft_lstnew(line);
		ft_lstadd_front(&a->gc, ft_lstnew(new_historic));
		ft_lstadd_back(&a->input->historic, new_historic);
	}
}

void	reset_variable_new_line(t_all *a, int *cursor, char **line)
{
	*cursor = 0;
	init_terms(a);
	*line = NULL;
	a->input->ctrl_c = 0;
	a->input->historic_current->content = "";
	a->input->ptr_historic = NULL;
	a->redir->chevron = 0;
}

void	ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line)
{
	ft_printf(1, "\n");
	if (*line && (*line)[0] != '\0')
	{
		stock_to_historic(a, *line);
		apply_termios(a->input->saved);
		stock_to_historic(a, *line);
		ft_lexing_command_line(*line, a);
	}
	if (a->input->read)// && !a->input->ctrl_c)
		display_line(a);
	reset_variable_new_line(a, cursor, line);
}
