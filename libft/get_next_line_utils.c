/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alafranc <alafranc@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 00:03:45 by alafranc          #+#    #+#             */
/*   Updated: 2021/05/27 10:37:01 by alafranc         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_supstr(char *s, unsigned int start, size_t len, int b)
{
	size_t	i;
	char	*str;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
	{
		str = malloc(1);
		str[0] = 0;
		if (b)
			free(s);
		return (str);
	}
	str = ft_calloc(len + 1, 1);
	if (!(str))
		return (NULL);
	while (s[start] != '\0' && (i < len))
		str[i++] = s[start++];
	if (b && s)
		free(s);
	str[i] = '\0';
	return (str);
}

int	ft_memchr_g(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (((unsigned char *)s)[i] == (unsigned char)c)
			return (i);
		i++;
	}
	return (-1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		c1;

	i = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && s2)
		c1 = ft_strlen(s1) + ft_strlen(s2);
	else if (!s1)
		c1 = ft_strlen(s2);
	else
		c1 = ft_strlen(s1);
	str = ft_calloc(c1 + 1, 1);
	c1 = 0;
	if (!(str))
		return (NULL);
	if (s1)
	{
		while (s1[i] != '\0')
		{
			str[i] = s1[i];
			i++;
		}
	}
	if (s2)
	{
		while (s2[c1] != '\0')
			str[i++] = s2[c1++];
	}
	str[i] = '\0';
	free(s1);
	return (str);
}
