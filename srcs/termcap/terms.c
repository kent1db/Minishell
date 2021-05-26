/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:11:34 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/26 11:11:40 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_terms(t_all *a)
{
	a->saved = save_termios();
	delete_special_characters();
	ft_pick_signal(a);
}