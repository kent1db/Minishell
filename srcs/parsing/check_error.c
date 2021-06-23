/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 14:42:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/23 17:14:28 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_put_status(t_all *a, int status)
{
	a->status = status;
	ft_status_cmd(a, &a->status);
}

int	ft_print_error_msg(t_all *a, char *msg, int return_nb)
{
	ft_printf(1, "minichiale: syntax error near unexpected token `%s'\n", msg);
	ft_put_status(a, 258);
	return (return_nb);
}

int	ft_check_empty_op(t_all *a, char *line, int index)
{
	int	n;
	int	i;

	i = 0;
	n = ft_strlen(line);
	if (line[0] == ';' && ((line[1] && line[1] != ';') || !line[1]))
		return (ft_print_error_msg(a, ";", ft_strlen(line) - index));
	while (line[i])
	{
		if (line[i] == ';' && line[i + 1] && line[i + 1] == ';')
			return (ft_print_error_msg(a, ";;", ft_strlen(line) - index));
		i++;
	}
	return (i - index);
}

int	ft_check_redir(t_all *a, char *line, int index)
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
				return (ft_print_error_msg(a, "<", ft_strlen(line) - index));
		}
		while (line[i] == '>')
		{
			count++;
			i++;
			if (count >= 2)
				return (ft_print_error_msg(a, ">", ft_strlen(line) - index));
		}
	}
	return (0);
}

int	ft_check_error(t_all *a, char *line, int index)
{
	if (a->tree->type == op_pipe && (a->tree->left->type != command ||\
	a->tree->right->type != command))
		return (ft_print_error_msg(a, "|", 0));
	if (a->tree->type == redir && a->tree->right->type != file)
		return (ft_print_error_msg(a, a->tree->exec->file->file,
		ft_strlen(line) - index));
	if (ft_check_redir(a, line, index))
		return (ft_check_redir(a, line, index));
	return (ft_check_empty_op(a, line, index));
}
