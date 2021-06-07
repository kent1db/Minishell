/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/06/07 11:33:26 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define CTRL_U 21
# define CTRL_L 12
# define DEL	127
# define BACKSPACE 8
# define CTRL_D		4
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
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
t_all			*init_all(char **envp, char *name_prg);
void			print_banner(void);
int				ft_switch_keyboard(t_all *a, char buf[4],
					int *cursor, char **line);
void			ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line);
void			ft_print_line_and_stock(t_all *a, char **line, char *buf, int *cursor);
int				ft_putchar_int(int c);
void			display_line(t_all *a);
void			ft_cmd_not_found(t_all *a, char *cmd);
/*
** ---------- TERMCAP ----------
*/
/*
**	ARROW_KEY
*/
void			ft_arrow_key(t_all *a, char c, int *cursor, char **line);
void			ft_left_arrow(int *cursor);
void			ft_right_arrow(int *cursor, int size_line);
void			ft_up_arrow(t_input *term, int *cursor, char **line, t_list **gc);
void			ft_down_arrow(t_input *term, int *cursor, char **line, t_list **gc);
/*
**	DELETE
*/
char			*delete_char(int index_char, char *str, t_list **gc);
void			ft_delete_line_to_cursor(t_list **gc, int *cursor, char **line);
void			ft_delete_line_from_cursor_into_line(t_list **gc, int *cursor, char **line);
void			ft_delete_line(t_list **gc, int *cursor, char **line);
void			ft_backspace(t_list **gc, int *cursor, char **line);
/*
**	INIT
*/
void			init_termios(void);
void			init_terms(t_all *a);
void			ft_init_input(t_all *a);
/*
**	PRINT
*/
int				ft_print_buf(char *str, int *cursor);
void			ft_print_buf_and_stock(t_all *a, char **line, char *buf, int *cursor);
/*
**	READ_CMD_LINE
*/
void			read_command_line(t_all *a);
int				ft_switch_keyboard(t_all *a, char buf[4], int *cursor, char **line);
void			ft_launch_cmd_and_reset(t_all *a, int *cursor, char **line);
/*
**	TERMIOS
*/
struct termios	get_termios(void);
void			apply_termios(struct termios termios);
/*
**	UTILITY
*/
t_list			*previous_current(t_list *lst, t_list *current, t_list *historic_current);
void			ft_change_line(t_list **gc, int *cursor, char **line, char *new_line);
char			*ft_add_string_in_index(t_list **gc, char **str_split, char *add);
char			**split_str_into_index(t_list **gc, char *str, int index);

/*
**	---------- CMD ----------
** 		---------- ENV ----------
*/
t_env			*ft_lstnew_env(char *key, char *content, t_status status);
t_env			*ft_lstlast_env(t_env *lst);
void			ft_lstadd_back_env(t_env **alst, t_env *new);
void			ft_lst_remove_key(t_env **env, char *key);
t_env			*ft_keyshr(t_env *env, char *key);
int				ft_env(t_all *a, t_command *cmd);
int				ft_export(t_all *a, t_command *cmd);
int				ft_unset(t_all *a, t_command *cmd);
int				ft_lstsize_env_status(t_env *env, t_status status);
char			**convert_env_to_strs(t_list **gc, t_env *env);
/*
** 		---------- LAUNCH ----------
*/
int				launch_if_is_our_cmd(t_command *cmd, t_all *a, char **cmd_done,
					int	(**ft_cmd)(t_all *a, t_command *cmd));
void			ft_launch_cmd(t_command *cmd, t_all *all);
void			ft_launch_execve_path_cmd(char **arg, t_all *a, t_command *cmd);
void			ft_exit_status_cmd(t_all *a);
int				ft_launch_execve_with_path(char *path_cmd, t_all *a,
					char **arg);
void			ft_launch_execve(t_command *cmd, t_all *a);
void			ft_point_on_split(t_list **gc, char **split);
char			**list_cmd_done(t_list **gc);
void			*init_array_instruction_function(t_list **gc);
char			**fill_argument_execve(t_all *a, char *args);
void			ft_point_gc_on_split(t_list **gc, char **split);
void			ft_fill_exit_status(t_all *a);
/*
**		---------- ROOT ----------
*/
int				ft_exit(t_all *a, t_command *cmd);
int				ft_echo(t_all *a, t_command *cmd);
/*	
** ---------- PARSING ----------
*/
void			ft_lexing_command_line(char *line, t_all *a);
t_env			*parse_env(char **env, t_list **gc);
t_env			*pick_key_and_content(char *envp, t_list **gc, t_status status);
#endif
