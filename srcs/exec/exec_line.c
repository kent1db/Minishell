/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 11:31:08 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/17 12:20:52 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_line(t_tree *node, t_all *a)
{
    if (node->type && node->type == op_pipe)
		ft_pipe(a);
	else if (node->type && node->type == redir)
	{
		ft_redir(node->exec->op, a);
		if (node->right != NULL)
			exec_line(node->right, a);
		if (node->left != NULL)
			exec_line(node->left, a);
		return ;
	}
	else if (node->type && node->type == command)
		ft_launch_cmd(node->exec->cmd, a);
	else if (node->type && node->type == file)
		ft_file(node, a);
	if (node->left != NULL)
		exec_line(node->left, a);
	if (node->right != NULL)
		exec_line(node->right, a);
}
