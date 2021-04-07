/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:56:01 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:56:02 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*mb;
	size_t			l;

	l = 0;
	mb = (unsigned char*)b;
	while (l < len)
	{
		mb[l] = c;
		l++;
	}
	return ((unsigned char *)b);
}
