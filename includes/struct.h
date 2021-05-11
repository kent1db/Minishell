/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/17 16:01:46 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/11 15:20:58 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef enum	e_status_env
{
	s_env,
	s_export,
	none
}				status_env;

typedef struct s_env
{
	char			*key;
	char			*content;
	status_env		status;
	struct s_env	*next;
}					t_env;

#endif