/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 10:47:01 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/27 16:13:38 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_special_characters(void)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	// termios.c_lflag &= (~ECHOCTL | ICANON | ~ECHO);
	// termios.c_lflag &= ~ICANON;
	// termios.c_lflag &= ECHOCTL;
	// termios.c_lflag &= ECHO;
	apply_termios(termios);
}

void	delete_or_add_eof(int is_add)
{
	struct termios	termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_cc[VEOF] = is_add;
	apply_termios(termios);
}

struct termios	get_termios(void)
{
	struct termios	saved;

	tcgetattr(STDIN_FILENO, &saved);
	return (saved);
}

void	apply_termios(struct termios termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}
