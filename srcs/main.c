/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/20 11:36:26 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_all *a)
{
	char	*line;

	line = NULL;
	ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		ft_lexing_command_line(line, a);
		ft_printf(1, RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_all *a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->env = parse_env(envp, &a->gc);
	// print_banner();
    read_command_line(a);
	ft_lauch_cmd(NULL, a);
	ft_lstclear(&a->gc, free);
	return (0);
}
