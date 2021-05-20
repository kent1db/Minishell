/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/19 11:44:55 by qurobert          #+#    #+#             */
/*   Updated: 2021/05/19 12:33:08 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef enum		e_type_enum
{
	type_command,
	type_operator,
	type_file
}					t_type_enum;

typedef struct		s_command
{
	char 			*cmd;
	char 			*args;
}					t_command;

typedef struct		s_operator
{
	char			*op;
}					t_operator;

typedef struct		s_file
{
	char			*file;
}					t_file;

typedef union		u_type_union
{
	t_command		cmd;
	t_operator		op;
	t_file			file;
}					t_type_union;

#endif
