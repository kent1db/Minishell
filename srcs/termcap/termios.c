/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 10:47:01 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/26 11:10:38 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_special_characters(void)
{
	struct termios termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_lflag &= ~ ECHOCTL;
	// DELETE EOF
	// termios.c_cc[VEOF] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

void	delete_or_add_eof(int is_add)
{
	struct termios termios;

	tcgetattr(STDIN_FILENO, &termios);
	termios.c_cc[VEOF] = is_add;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}

struct termios save_termios(void)
{
	struct termios saved;

	tcgetattr(STDIN_FILENO, &saved);	
	return (saved);
}

void	apply_termios(struct termios termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &termios);
}