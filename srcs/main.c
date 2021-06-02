/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 09:39:47 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/02 15:45:41 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

t_all	*init_all(char **envp)
{
	t_all	*a;

	a = malloc(sizeof(t_all));
	a->gc = NULL;
	ft_lstadd_front(&a->gc, ft_lstnew(a));
	a->status_cmd = 0;
	a->env = parse_env(envp, &a->gc);
	a->termcap = malloc_gc(&a->gc, (sizeof(t_termcap)));
	a->termcap->historic = NULL;
	a->termcap->historic_current = ft_lstnew("");
	ft_lstadd_front(&a->gc, ft_lstnew(a->termcap->historic_current));
	a->termcap->ptr_historic = NULL;
	a->read = 1;
	set_all(a);
	return (a);
}

int	main(int ac, char **av, char **envp)
{
	t_all	*a;	

	(void)ac;
	(void)av;
	errno = 0;
	a = init_all(envp);
	init_terms(a);
	print_banner();
	read_command_line(a);
	ft_printf(1, "exit\n");
	apply_termios(a->termcap->saved);
	ft_lstclear(&a->gc, free);
	return (0);
}
