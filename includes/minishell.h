<<<<<<< HEAD
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/18 13:04:07 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
=======
>>>>>>> 20142365ec69353a59bec42462ddb10b8df2cca7

#ifndef MINISHELL_H
# define MINISHELL_H
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
t_env	*pick_key_and_content(char *envp, t_list **gc, status status);
/*
**	FT_LST_ENV
*/
t_env	*ft_lstnew_env(char *key, char *content, status status);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lst_remove_key(t_env **env, char *key);
/*
**	FT_CLI_ENV
*/
void	ft_env(t_env *env);
void	ft_export(t_env **env, char **args, t_list **gc);
void	ft_unset(t_env **env, char **args);
/*
**	FT_UTILITY_ENV
*/
t_env	*ft_keyshr(t_env *env, char *key);
/*
** ---------- CMD ----------
**	FT_CMD
*/
void ft_lauch_cmd(char *cmds, t_list **gc);
#endif
