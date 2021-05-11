/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:12:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/11 14:58:22 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_env **env, t_list **gc)
{
	char	*line;

	(void)gc;
	(void)env;
	line = NULL;
	ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
	while (get_next_line(0, &line))
	{
		ft_printf(RED "➜ " BLU "minishell " YEL "✗ " RESET);
		free(line);
	}
}

int	main(int ac, char **av, char **envp)
{
	t_env *env;
	t_list *gc;

	gc = NULL;
	env = parse_env(envp, &gc);
	print_banner();
    read_command_line(&env, &gc);
	ft_lstclear(&gc, free);
	return (0);
}