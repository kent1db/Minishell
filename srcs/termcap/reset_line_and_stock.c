/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:39:20 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/08 16:17:00 by alafranc         ###   ########lyon.fr   */
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
}

void	stock_cmd(t_command *cmd, char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd->cmd = ft_substr(line, 0, i);
	cmd->args = ft_substr(line, i + 1, ft_strlen(line) - i + 1);
}

void	ft_print_cmd(t_command *cmd)
{
	if (!cmd)
	{
		ft_printf(1, "cmd NULL\n");
		return ;
	}
	if (cmd->cmd)
		ft_printf(1, "cmd: %s\n", cmd->cmd);
	if (cmd->args)
		ft_printf(1, "args: %s\n", cmd->args);
}

void	ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line)
{
	t_command	*cmd;

	ft_printf(1, "\n");
	if (*line && (*line)[0] != '\0')
	{
		stock_to_historic(a, *line);
		apply_termios(a->input->saved);
		cmd = malloc_gc(&a->gc, sizeof(t_command));
		stock_cmd(cmd, *line); // JUST FOR TEST WHITOUT PARSING
		cmd->cmd = delete_quote(cmd->cmd);
		ft_lstadd_front(&a->gc, ft_lstnew(cmd->cmd));
		ft_launch_cmd(cmd, a);
	}
	if (a->input->read)// && !a->input->ctrl_c)
		display_line(a);
	reset_variable_new_line(a, cursor, line);
}
