/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 23:23:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/25 15:49:56 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include "minishell.h"

void    fct_signal(int a)
{
    ft_printf(1, RED "\n➜ " BLU "minishell " YEL "✗ " RESET);
}

void    ft_pick_signal(t_all *a)
{
    // CTRL+C
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        ft_error_msg("signal have a error", a->gc);
        return ;
    }

    // CTRL+\

    if (signal(SIGINT, fct_signal) == SIG_ERR)
    {
        ft_error_msg("signal have a error", a->gc);
        return ;
    }
    // struct termios saved;
    // struct termios attributes;

    // tcgetattr(STDIN_FILENO, &saved);

    // tcgetattr(STDIN_FILENO, &attributes);
    // attributes.c_lflag &= ~ ECHO;
    // tcsetattr(STDIN_FILENO, TCSAFLUSH, &attributes);
    // while (1);
}
