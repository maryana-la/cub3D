/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:56:10 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:56:11 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	int				res;
	unsigned char	*ss1;
	unsigned char	*ss2;

	i = 0;
	res = 0;
	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (n != 0)
	{
		while (ss1[i] == ss2[i] && ss1[i] != '\0' && ss2[i] != '\0'
				&& (i + 1) < n)
		{
			i++;
		}
		if (ss1[i] > ss2[i])
			return (1);
		if (ss1[i] < ss2[i])
			return (-1);
		else
			return (0);
	}
	else
		return (0);
}
