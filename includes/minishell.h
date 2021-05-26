/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/25 15:54:46 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
#include <curses.h>
#include <term.h>
# include "../libft/libft.h"
# include "color.h"
# include "struct.h"

/*
**	GARBAGE COLLECTOR
*/
void	*malloc_gc(t_list **gc, size_t size);
char	*ft_strdup_gc(t_list **gc, char *src);
/*
**	FT_ERROR
*/
void	ft_error_msg(char *msg_error, t_list *gc);
/*
**	FT_PICK_SIGNAL
*/
void    ft_pick_signal(t_all *a);
/*
**	MAIN
*/
void	read_command_line(t_all *a);
t_all	*init_all(char **envp);
/*	
** ---------- DISPLAY ----------
**	PRINT_BANNER
*/
void	print_banner(void);
/*
**	---------- CMD ----------
** 		---------- ENV ----------
**			FT_LST_ENV
*/
t_env		*ft_lstnew_env(char *key, char *content, t_status status);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **alst, t_env *new);
void		ft_lst_remove_key(t_env **env, char *key);
t_env		*ft_keyshr(t_env *env, char *key);
/*
**			FT_CLI_ENV
*/
int			ft_env(t_all *a);
int			ft_export(t_all *a);
int			ft_unset(t_all *a);
/*
** 		---------- LAUNCH ----------
**			FT_LAUNCH_CMD
*/
int			launch_if_is_our_cmd(char *cmd, t_all *a, char **cmd_done,
								int	(**ft_cmd)(t_all *a));
void		ft_launch_cmd(char *cmd, t_all *all, char *name_prg);
void		ft_exit_status_cmd(t_all *a);
/*
**			FT_LAUNCH_EXECVE
*/
int			ft_launch_execve_with_path(char *path_cmd, t_all *a, char **arg);
void		ft_launch_execve(char *cmd, t_all *a, char *name_prg);
void		ft_point_on_split(t_list **gc, char **split);
/*
**			POINTER_ARRAY_FCT_CMD
*/
char		**list_cmd_done(t_list **gc);
void		*init_array_instruction_function(t_list **gc);
char		**pick_argument_and_add_name_prg(t_all *a, char *name_prg);
void		ft_point_gc_on_split(t_list **gc, char **split);
/*
**		EXIT_STATUS
*/
void	ft_fill_exit_status(t_all *a);
/*
** ---------- PARSING ----------
**		PARSE_ARG
*/
void	ft_lexing_command_line(char *line, t_all *a);
/*
**		PARSE_ENV
*/
t_env	*parse_env(char **env, t_list **gc);
t_env	*pick_key_and_content(char *envp, t_list **gc, t_status status);
#endif
