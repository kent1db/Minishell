/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:12:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/18 10:58:57 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_env **env, t_list **gc)
{
	char	*line;

	(void)env;
	line = NULL;
	ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		ft_parse_command_line(gc, line);
		ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *env;
	t_list *gc;
	int		i = 0;

	gc = NULL;
	env = parse_env(envp, &gc);
	print_banner();
    read_command_line(&env, &gc);
	ft_lstclear(&gc, free);
	return (0);
}
