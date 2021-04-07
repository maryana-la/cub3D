/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:46 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:47 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../srcs/cub3d.h"

int	ft_atoi_cub(const char *str)
{
	int					minus;
	unsigned long long	num;

	num = 0;
	minus = 1;
	while (*str == '\t' || *str == '\n' || *str == ' ' ||
			*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			minus = -minus;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		num = (num * 10) + (*str - 48);
		if (num > 10000)
			return ((int)(10000 * minus));
		str++;
	}
	return (minus * (int)num);
}
