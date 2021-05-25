/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:10:33 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/21 11:26:06 by alafranc         ###   ########lyon.fr   */
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

typedef struct s_env

{
	char			*key;
	char			*content;
	t_status		status;
	struct s_env	*next;
}					t_env;

typedef	struct		s_tree
{	
	struct s_btree	*left;
	struct s_btree	*right;
	t_type_enum		type;
	t_type_union	exec;
}					t_tree;

typedef struct s_all
{
	t_env	*env;
	t_list	*gc;
	t_tree	*tree;
	int		status_cmd;
}				t_all;

#endif
