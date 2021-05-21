/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qurobert <qurobert@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/21 10:08:30 by qurobert         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>
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
** ---------- DISPLAY ----------
**	PRINT_BANNER
*/
void	print_banner(void);
/*
** ---------- ENV ----------
**	PARSE_ENV
*/
t_env	*parse_env(char **env, t_list **gc);
t_env	*pick_key_and_content(char *envp, t_list **gc, t_status status);
/*
**	FT_LST_ENV
*/
t_env	*ft_lstnew_env(char *key, char *content, t_status status);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lst_remove_key(t_env **env, char *key);
/*
**	FT_CLI_ENV
*/
int		ft_env(t_all *a);
int		ft_export(t_all *a);
int		ft_unset(t_all *a);
/*
**	FT_UTILITY_ENV
*/
t_env	*ft_keyshr(t_env *env, char *key);
/*
** ---------- CMD ----------
**	FT_FILL_ARRAY_OUR_CMD
*/
char	**list_cmd_done(t_list **gc);
void	*init_array_instruction_function(t_list **gc);
/*
**	FT_LAUNCH_CMD
*/
void ft_launch_cmd(char *cmd, t_all *all, char *name_prg);
/*	
** ---------- PARSING ----------
*/
void	ft_lexing_command_line(char *line, t_all *a);
#endif
