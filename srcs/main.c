/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:12:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/17 19:13:28 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	read_command_line(t_env **env, t_list **gc)
{
	char	*line;

	(void)gc;
	(void)env;
	line = NULL;
	dprintf(1, "%s➜  %sminishell %s✗%s ", RED, BLU, YEL, RESET);
	while (get_next_line(0, &line))
	{
		dprintf(1, "%s➜  %sminishell %s✗%s ", RED, BLU, YEL, RESET);
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
	read_command_line(env, gc);
	ft_lstclear(&gc, free);
	return (0);
}
