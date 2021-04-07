/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:50:52 by rchelsea          #+#    #+#             */
/*   Updated: 2020/12/20 20:50:55 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	while (str[i] != 0)
		i++;
	return (i);
}

char	*ft_strdup(char *s1)
{
	size_t	len;
	char	*dest;
	int		i;

	i = 0;
	len = ft_strlen(s1) + 1;
	dest = (char *)malloc(len);
	if (dest == 0)
		return (NULL);
	while (s1[i] != '\0')
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(char *s, int c)
{
	if (c == '\0')
	{
		while (*s != '\0')
			s++;
		return ((char*)s);
	}
	while (*s != '\0')
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	return (NULL);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!(new))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char	*ft_strmove(char *ddst, char *ssrc, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	j = len;
	if (ddst == NULL && ssrc == NULL)
		return (NULL);
	if (ssrc > ddst)
	{
		while (ssrc[i] != '\0')
		{
			ddst[i] = ssrc[i];
			i++;
		}
		ddst[i] = '\0';
	}
	else
	{
		while (len--)
			ddst[len] = ssrc[len];
		ddst[j] = '\0';
	}
	return (ddst);
}
