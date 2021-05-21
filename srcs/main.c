/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/21 14:14:07 by alafranc         ###   ########lyon.fr   */
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

t_all	*init_all(char **envp)
{
	t_all *a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->status_cmd = 0;
	a->env = parse_env(envp, &a->gc);
	return (a);
}

int	main(int ac, char **av, char **envp)
{
	t_all *a;

	errno = 0;
	a = init_all(envp);
	// print_banner();
    // read_command_line(&env, &gc);
	ft_launch_cmd("./ls", a, av[0]);
	ft_exit_status_cmd(a);
	ft_printf(1, "echo $? : %s", ft_keyshr(a->env, "?")->content);
	ft_lstclear(&a->gc, free);
	return (0);
}
