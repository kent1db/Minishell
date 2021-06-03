/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmd_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/30 14:42:57 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/03 13:34:39 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_all *a)
{
	char	buf[4];
	int		cursor;
	char	*line;

	line = NULL;
	cursor = 0;
	ft_bzero(buf, 3);
	display_line(a);
	while (a->read && read(0, buf, 3))
	{
		if (ft_switch_keyboard(a, buf, &cursor, &line))
			break ;
		ft_bzero(buf, 3);
	}
}

void	ft_ctrl_l(t_all *a, char *line)
{
	t_command *cmd;

	cmd = malloc_gc(&a->gc, sizeof(t_command));
	cmd->cmd = ft_strdup_gc(&a->gc, "clear");
	cmd->opt = NULL;
	cmd->args = NULL;
	ft_launch_cmd(cmd, a, a->name_prg);
	display_line(a);
	if (line)
		ft_printf(1, "%s", line);
}

int	ft_switch_keyboard(t_all *a, char buf[4], int *cursor, char **line)
{
	if (buf[0] == CTRL_D)
	{
		if (*cursor == 0)
			return (1);
	}
	else if (buf[0] == BACKSPACE || buf[0] == DEL)
		ft_backspace(&a->gc, cursor, line);
	else if (buf[0] == CTRL_U)
		ft_delete_line_to_cursor(&a->gc, cursor, line);
	else if (buf[0] == CTRL_L)
		ft_ctrl_l(a, *line);
	else if (buf[1] == '[')
		ft_arrow_key(a, buf[2], cursor, line);
	else if (buf[0] == '\n')
		ft_launch_cmd_and_reset(a, cursor, line);
	else
		ft_print_buf_and_stock(a, line, buf, cursor);
	return (0);
}

void	stock_to_historic(t_all *a, char *line)
{
	t_list  *new_historic;

	if (line && line[0] != '\0')
	{
		new_historic = ft_lstnew(line);
		ft_lstadd_front(&a->gc, ft_lstnew(new_historic));
		ft_lstadd_back(&a->termcap->historic, new_historic);
	}
}

void	reset_variable_new_line(t_all *a, int *cursor, char **line)
{
	*cursor = 0;
	init_terms(a);
	*line = NULL;
	a->ctrl_c = 0;
	a->termcap->historic_current->content = "";
	a->termcap->ptr_historic = NULL;
}

void	strs_add_to_gc(char **strs, t_list **gc)
{
	int		i;

	i = -1;
	ft_lstadd_front(gc, ft_lstnew(strs));
	if (!strs)
		return ;
	while (strs[++i])
		ft_lstadd_front(gc, ft_lstnew(strs[i]));
}

void	ft_print_strs(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i])
		ft_printf(1, "%s\n", strs[i]);
}

void	stock_cmd(t_command *cmd, char **line_split)
{
	int i;

	if (!line_split)
	{
		cmd->cmd = NULL;
		cmd->args = NULL;
		cmd->opt = NULL;
		return ;
	}
	else if (ft_strslen(line_split) >= 3)
	{
		cmd->cmd = line_split[0];
		cmd->opt = line_split[1];
		i = 1;
		cmd->args = NULL;
		while (line_split[++i])
		{
			cmd->args = ft_strjoin_free(cmd->args, line_split[i]);
			cmd->args = ft_strjoin_free(cmd->args, " ");
		}
	}
	else if (ft_strslen(line_split) == 2)
	{
		cmd->cmd = line_split[0];
		cmd->opt = NULL;
		cmd->args = line_split[1];
	}
	else
	{	
		cmd->cmd = line_split[0];
		cmd->opt = NULL;
		cmd->args = NULL;
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
	if (cmd->cmd)
		ft_printf(1, "opt: %s\n", cmd->opt);
	if (cmd->args)
		ft_printf(1, "args: %s\n", cmd->args);
}



void	ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line)
{
	t_command	*cmd;
	char		**line_split;

	cmd = malloc_gc(&a->gc, sizeof(t_command));
	line_split = ft_split(*line, ' ');
	strs_add_to_gc(line_split, &a->gc);
	apply_termios(a->termcap->saved);
	ft_printf(1, "\n");
	stock_to_historic(a, *line);
	stock_cmd(cmd, line_split);
	// ft_print_cmd(cmd);
	ft_launch_cmd(cmd, a, "./minishell");	
	if (a->read && !a->ctrl_c)
		display_line(a);
	reset_variable_new_line(a, cursor, line);
}
