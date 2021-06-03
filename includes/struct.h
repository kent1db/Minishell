/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/06/03 12:34:30 by alafranc         ###   ########lyon.fr   */
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

typedef struct s_termcap
{
	struct termios	saved;
	t_list			*historic;
	t_list			*historic_current;
	t_list			*ptr_historic;	
}				t_termcap;

typedef struct s_all
{
	t_env			*env;
	t_list			*gc;
	t_tree			*tree;
	int				status_cmd;
	t_termcap		*termcap;
	int				read;
	int				ctrl_c;
	char			*name_prg;
}				t_all;


#endif
