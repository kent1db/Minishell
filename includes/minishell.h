/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/16 17:11:02 by alafranc          #+#    #+#             */
/*   Updated: 2021/04/18 20:41:28 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

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
t_env	*pick_key_and_content(char *envp, t_list **gc);
/*
**	FT_LST_ENV
*/
t_env	*ft_lstnew_env(char *key, char *content, int is_push);
t_env	*ft_lstlast_env(t_env *lst);
void	ft_lstadd_back_env(t_env **alst, t_env *new);
void	ft_lst_remove_key(t_env **env, char *key);
/*
**	FT_CLI_ENV
*/
void	ft_env(t_env *env);
void	ft_export(t_env **env, char **args);
void	ft_unset(t_env **env, char **args);
#endif