/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:56:15 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:56:16 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

char		*ft_substr(char *s, unsigned int start, size_t len)
{
	char			*new;
	unsigned int	i;

	if (!s)
		return (NULL);
	new = (char *)malloc(len + 1);
	if (new == NULL)
		return (NULL);
	i = 0;
	if (ft_strlen(s) <= start)
	{
		*new = 0;
		return (new);
	}
	if (ft_strlen(s) > start)
	{
		while (s[start] && i < len)
			new[i++] = s[start++];
		new[i] = '\0';
		return (new);
	}
	else
		return (0);
}

static	int	check(char *basic, char letter)
{
	size_t	i;

	i = 0;
	while (basic[i] != '\0' && basic[i] != letter)
		i++;
	if (basic[i] == letter)
		return (1);
	else
		return (0);
}

char		*ft_strtrim(char *s1, char *set)
{
	char	*new;
	int		i;
	int		len_s1;

	if (!s1)
		return (0);
	len_s1 = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] != '\0' && check(set, s1[i]) == 1)
		i++;
	while (len_s1 >= 0 && check(set, s1[len_s1]) == 1)
		len_s1--;
	if (len_s1 < i)
		return (ft_substr(s1, i, len_s1));
	new = ft_substr(s1, i, (len_s1 - i + 1));
	return (new);
}
