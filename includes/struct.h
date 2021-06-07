/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/04 13:00:32 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "exec.h"

typedef enum e_status
{
	status_env,
	status_export,
	status_none
}				t_status;

typedef struct s_env
{
	char			*key;
	char			*content;
	t_status		status;
	struct s_env	*next;
}					t_env;

typedef struct s_tree
{	
	struct s_btree	*left;
	struct s_btree	*right;
	t_type_enum		type;
	t_type_union	*exec;
}					t_tree;

typedef struct s_input
{
	int				read;
	int				ctrl_c;
	struct termios	saved;
	t_list			*historic;
	t_list			*historic_current;
	t_list			*ptr_historic;	
}				t_input;

typedef struct s_all
{
	t_env			*env;
	t_list			*gc;
	t_tree			*tree;
	t_input			*input;
	int				status_cmd;
	int				in_cmd;
	char			*name_prg;
}				t_all;


#endif
