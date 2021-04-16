/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 15:12:11 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/16 17:25:43 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
int	main(int ac, char **av, char **env)
{
	char *line;

	line = NULL;
	print_banner();
	while (get_next_line(0, &line))
	{
		dprintf(1, "coucou");
	}
	return (0);
}
