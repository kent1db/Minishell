/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/28 13:23:32 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include "../libft/libft.h"
# include "color.h"
# include "struct.h"
/*
**	---------- SRCS ----------
*/
void			*malloc_gc(t_list **gc, size_t size);
char			*ft_strdup_gc(t_list **gc, char *src);
void			ft_error_msg(char *msg_error, t_list *gc);
t_all			*set_all(t_all *tmp);
t_all			*get_all(void);
void			read_command_line(t_all *a);
t_all			*init_all(char **envp);
void			print_banner(void);
void			display_line(t_all *a);
/*
** ---------- TERMCAP ----------
*/
void			init_termios(void);
void			delete_or_add_eof(int is_add);
struct termios	get_termios(void);
void			apply_termios(struct termios termios);
void			ft_pick_signal(t_all *a);
void			init_terms(t_all *a);
void			ft_init_termcap(t_all *a);
void			ft_backspace(t_all *a, int *cursor, t_list **line);
void			ft_left_arrow(t_all *a, int *cursor);
void			ft_right_arrow(t_all *a, int *cursor, t_list *line);
char			*transform_to_str(t_list *lst, t_list **gc);
void			ft_lst_remove_index(t_list **str, int remove_index);
void			ft_print_list(t_list *lst);
/*
**	---------- CMD ----------
** 		---------- ENV ----------
*/
t_env			*ft_lstnew_env(char *key, char *content, t_status status);
t_env			*ft_lstlast_env(t_env *lst);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lst_remove_key(t_env **env, char *key);
t_env			*ft_keyshr(t_env *env, char *key);
int				ft_env(t_all *a);
int				ft_export(t_all *a);
int				ft_unset(t_all *a);
/*
** 		---------- LAUNCH ----------
*/
int				launch_if_is_our_cmd(char *cmd, t_all *a, char **cmd_done,
					int	(**ft_cmd)(t_all *a));
void			ft_launch_cmd(char *cmd, t_all *all, char *name_prg);
void			ft_exit_status_cmd(t_all *a);
int				ft_launch_execve_with_path(char *path_cmd, t_all *a,
					char **arg);
void			ft_launch_execve(char *cmd, t_all *a, char *name_prg);
void			ft_point_on_split(t_list **gc, char **split);
char			**list_cmd_done(t_list **gc);
void			*init_array_instruction_function(t_list **gc);
char			**pick_argument_and_add_name_prg(t_all *a, char *name_prg);
void			ft_point_gc_on_split(t_list **gc, char **split);
void			ft_fill_exit_status(t_all *a);
/*	
** ---------- PARSING ----------
*/
void			ft_lexing_command_line(char *line, t_all *a);
t_env			*parse_env(char **env, t_list **gc);
t_env			*pick_key_and_content(char *envp, t_list **gc, t_status status);
#endif
