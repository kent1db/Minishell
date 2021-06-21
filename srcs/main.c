//* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/15 12:37:06 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>

t_all	*set_all(t_all *tmp)
{
	static t_all	*all;

	if (tmp)
		all = tmp;
	return (all);
}

t_all	*get_all(void)
{
	return (set_all(NULL));
}

t_all	*init_all(char **envp, char *name_prg)
{
	t_all	*a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->status = 0;
	a->env = parse_env(envp, &a->gc);
	a->input = malloc_gc(&a->gc, (sizeof(t_input)));
	a->input->historic = NULL;
	a->input->historic_current = ft_lstnew("");
	ft_lstadd_front(&a->gc, ft_lstnew(a->input->historic_current));
	a->input->ptr_historic = NULL;
	a->read = 1;
	a->in_cmd = 0;
	a->redir = malloc_gc(&a->gc, sizeof(t_redir));
	reset_redir(a->redir);
	a->pipe = malloc_gc(&a->gc, sizeof(t_pipe));
	a->pipe->fd = malloc_gc(&a->gc, sizeof(int) * 2);
	a->pipe->fd_backup = malloc_gc(&a->gc, sizeof(int) * 3);
	reset_pipe(a->pipe);
	a->name_prg = name_prg;
	ft_lstadd_back_env(&a->env, ft_lstnew_env("?", "0", status_none));
	set_all(a);
	return (a);
}

int	main(int ac, char **av, char **envp)
{
	t_all	*a;	

	(void)ac;
	(void)av;
	errno = 0;
	a = init_all(envp, av[0]);
	init_terms(a);
	print_banner();
	read_command_line(a);
	ft_printf(1, "exit\n");
	apply_termios(a->input->saved);
	ft_lstclear(&a->gc, free);
	return (0);
}
