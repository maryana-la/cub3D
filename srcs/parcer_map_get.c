/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_map_get.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:57 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:58 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_store_map_to_struct(t_all *all, t_parse *p)
{
	if (all->num_sprites > 0)
	{
		if (!(all->sprite = malloc(sizeof(t_sprite) * (all->num_sprites + 1))))
			ft_map_parse_error(all, MEM_ERROR);
	}
	if (!(all->map = ft_calloc(sizeof(char *), (p->str_count + 2))))
		ft_map_parse_error(all, MEM_ERROR);
	ft_str_to_array(all, p);
	ft_verify_map(p, all->map, p->x);
	if (p->err < 0)
		ft_map_check_error(all, p->x, p->err);
}

void	ft_str_to_array(t_all *all, t_parse *p)
{
	int z;

	z = -1;
	while (p->str[p->k] != '\0' && p->k < (p->dlina_str + 1))
	{
		if (!(all->map[p->x] = ft_calloc(sizeof(char), (p->max_len + 1))))
			ft_map_check_error(all, p->x, MEM_ERROR);
		p->y = 0;
		while (p->str[p->k] != '\n')
		{
			if (p->str[p->k] == '2')
				ft_set_sprite(p->x, p->y, ++z, all);
			all->map[p->x][p->y++] = p->str[p->k++];
		}
		if (p->str[p->k] == '\n' && p->str[p->k - 1] == '\n')
			ft_map_check_error(all, p->x, MAP_EMP_LINE);
		if (p->y < p->max_len - 1)
		{
			while (p->y < p->max_len)
				all->map[p->x][p->y++] = ' ';
		}
		p->x++;
		p->k++;
	}
	all->map[p->x] = NULL;
}

int		ft_verify_map(t_parse *p, char **map, int arr_len)
{
	int i;
	int j;

	i = -1;
	while (++i < arr_len)
	{
		j = -1;
		while (++j < p->max_len)
		{
			if ((i == 0 || i == (arr_len - 1)) || (j == 0 ||
					j == (p->max_len - 1)))
			{
				if (map[i][j] == '0' || map[i][j] == '2')
					return (p->err = MAP_PERIM);
			}
			else
			{
				if (ft_check_inside_map(map, i, j) < 0)
					return (p->err = MAP_HOLES);
			}
		}
	}
	return (1);
}

int		ft_check_inside_map(char **map, int i, int j)
{
	if (map[i][j] == '0' || map[i][j] == '2')
	{
		if (map[i][j - 1] == ' ' || map[i - 1][j] == ' ')
			return (-1);
	}
	if (map[i][j] == ' ')
	{
		if (map[i][j - 1] == '0' || map[i - 1][j] == '0' ||
			map[i][j - 1] == '2' || map[i - 1][j] == '2')
			return (-1);
	}
	return (1);
}
