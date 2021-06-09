/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/09 14:36:20 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "exec.h"

typedef enum		e_status
{
	status_env,
	status_export,
	status_none
}				t_status;

typedef enum	e_error
{
	error_none,
	cmd_not_found = 127
}				t_error;

typedef struct s_env

{
	char			*key;
	char			*content;
	t_status		status;
	struct s_env	*next;
}					t_env;

typedef	struct		s_tree
{	
	struct s_tree	*left;
	struct s_tree	*right;
	int				type;
	t_type_enum		e_type;
	t_type_union	*exec;
	int				count;
	int				loop;
	int				start;
	int				end;
	char			*line;
}					t_tree;

typedef struct s_all
{
	t_env	*env;
	t_list	*gc;
	t_tree	*tree;
	t_error	error;
}				t_all;

#endif
