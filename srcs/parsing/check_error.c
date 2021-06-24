/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:42:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/24 11:22:02 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_status(t_all *a, int status)
{
	a->status = status;
	ft_status_cmd(a, &a->status);
}

int	ft_print_error_msg(t_all *a, char *msg)
{
	ft_printf(1, "minichiale: syntax error near unexpected token `%s'\n", msg);
	ft_put_status(a, 258);
	return (1);
}

int	ft_check_empty_op(t_all *a, char *line)
{
	int	n;
	int	i;

	i = 0;
	n = ft_strlen(line);
	if (line[0] == ';' && ((line[1] && line[1] != ';') || !line[1]))
		return (ft_print_error_msg(a, ";"));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] && line[i + 1] == ';')
			return (ft_print_error_msg(a, ";;"));
		i++;
	}
	return (0);
}

int	ft_check_redir(t_all *a, char *line)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (line[++i])
	{
		while (line[i] == '<')
		{
			count++;
			i++;
			if (count >= 2)
				return (ft_print_error_msg(a, "<"));
		}
		while (line[i] == '>')
		{
			count++;
			i++;
			if (count >= 2)
				return (ft_print_error_msg(a, ">"));
		}
	}
	return (0);
}

int	ft_check_error(t_all *a, char *line)
{
	if (a->tree->type == op_pipe && (a->tree->left->type != command ||\
	a->tree->right->type != command))
		return (ft_print_error_msg(a, "|"));
	if (a->tree->type == redir && a->tree->right->type != file)
		return (ft_print_error_msg(a, a->tree->exec->file->file));
	if (ft_check_redir(a, line))
		return (1);
	return (ft_check_empty_op(a, line));
}
