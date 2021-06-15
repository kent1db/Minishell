/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_line_and_stock.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/04 12:39:20 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/15 11:11:29 by alafranc         ###   ########lyon.fr   */
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

void	stock_cmd(t_command *cmd, char **line_split)
{
	int i;

	if (!line_split)
	{
		cmd->cmd = NULL;
		cmd->args = NULL;
		return ;
	}
	else if (ft_strslen(line_split) == 2)
	{
		cmd->cmd = line_split[0];
		cmd->args = NULL;
	}
	else
	{
		cmd->cmd = line_split[0];
		i = 1;
		cmd->args = NULL;
		while (line_split[++i])
		{
			cmd->args = ft_strjoin_free(cmd->args, line_split[i]);
			cmd->args = ft_strjoin_free(cmd->args, " ");
		}
	}
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
	// t_command	*cmd;
	// char		**line_split;

	ft_printf(1, "\n");
	if (line && *line && (*line)[0] != '\0')
	{
		apply_termios(a->input->saved);
		// cmd = malloc_gc(&a->gc, sizeof(t_command));
		// line_split = ft_split(*line, ' '); // JUST FOR TEST WHITOUT PARSING
		// ft_strs_add_to_gc(line_split, &a->gc); // JUST FOR TEST WHITOUT PARSING
		stock_to_historic(a, *line);
		// stock_cmd(cmd, line_split); // JUST FOR TEST WHITOUT PARSING
		ft_lexing_command_line(*line, a);
		// ft_launch_cmd(cmd, a);
	}
	if (a->input->read)// && !a->input->ctrl_c)
	display_line(a);
	reset_variable_new_line(a, cursor, line);
}
