/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:52 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:53 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *mem;

	mem = malloc(count * size);
	if (mem == NULL)
		return (NULL);
	ft_memset(mem, 0, count * size);
	return (mem);
}
