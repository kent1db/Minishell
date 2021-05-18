/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:01:46 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/17 10:43:08 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_status
{
	status_env,
	status_export,
	none
}				status;

typedef struct s_env
{
	char			*key;
	char			*content;
	status			status;
	struct s_env	*next;
}					t_env;

#endif