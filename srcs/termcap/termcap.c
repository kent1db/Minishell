/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/27 14:08:59 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/28 13:23:31 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_putchar_int(int a)
{
	write(1, &a, 1);
	return (1);	
}

// char *delete_char(int index_char, char *str, t_list *gc)
// {
// 	int		i;
// 	char	*new_str;

// 	new_str = malloc(sizeof(char) * ft_strlen(str));
// 	if (!new_str)
// 		ft_error_msg("Malloc error", gc);
// 	i = -1;
// 	while (str[++i])
// 	{
// 		if (i != index_char)
// 			new_str[i] = str[i];
// 	}
// 	new_str[i] = '\0';
// 	free(str);
// 	return (new_str);
// }

// char	*add_char(char *str, char c, t_list *gc)
// {
// 	int	i;
// 	char	*new_str;
// 	int	size_str;

// 	if (!str)
// 	{
// 		new_str = ft_calloc(2, sizeof(char));
// 		new_str[0] = c;
// 		return (new_str);
// 	}
// 	size_str = ft_strlen(str);
// 	new_str = malloc(sizeof(char) * (size_str + 1));
// 	if (!new_str)
// 		ft_error_msg("Malloc error", gc);
// 	ft_strcpy(new_str, str);
// 	new_str[size_str - 1] = c;
// 	new_str[size_str] = '\0';
// 	return (new_str);
// }

char	*transform_to_str(t_list *lst, t_list **gc)
{
	char	*str;
	int		i;

	i = 0;
	str = malloc_gc(gc, sizeof(char) * (ft_lstsize(lst) + 1));
	while (lst)
	{
		str[i] = (char)lst->content;
		lst = lst->next;
	}
	return (str);
}

void	ft_lst_remove_index(t_list **str, int remove_index)
{
	t_list	*begin;
	int		i;

	i = 0;
	begin = *str;
	if (!remove_index)
	{
		*str = (*str)->next;
		return ;
	}
	while (*str && (*str)->next)
	{
		if (i == remove_index)
		{
			(*str)->next = (*str)->next->next;
			*str = begin;
			return ;
		}
		*str = (*str)->next;
	}
	*str = begin;
}

void	ft_print_list(t_list *lst)
{
	while(lst)
	{
		ft_printf(1, "%s", lst->content);
		lst = lst->next;
	}
}

void	ft_backspace(t_all *a, int *cursor, t_list **line)
{
	if (*cursor == 0)
		return ;
	ft_lst_remove_index(line, *cursor);
	tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	tputs(tgetstr("dc", NULL), 1, ft_putchar_int);
	(*cursor)--;
}

void	ft_left_arrow(t_all *a, int *cursor)
{
	if (*cursor == 0)
		return ;
	tputs(tgetstr("le", NULL), 1, ft_putchar_int);
	(*cursor)--;
}

void	ft_right_arrow(t_all *a, int *cursor, t_list *line)
{
	if (ft_lstsize(line) <= *cursor)
		return ;
	tputs(tgetstr("nd", NULL), 1, ft_putchar_int);
	(*cursor)++;
}
