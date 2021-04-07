/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:26 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:27 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cub_exit(t_all *all)
{
	if (all->win.mlx && all->win.win)
	{
		mlx_clear_window(all->win.mlx, all->win.win);
		mlx_destroy_window(all->win.mlx, all->win.win);
	}
	ft_free_texture(all);
	ft_free_splt(all->map);
	if ((all->dist_buf))
	{
		free(all->dist_buf);
		all->dist_buf = NULL;
	}
	if (all->num_sprites > 0)
	{
		if ((all->sprite))
		{
			free(all->sprite);
			all->sprite = NULL;
		}
	}
	exit(0);
}

void	ft_free_texture(t_all *all)
{
	int i;

	i = 0;
	while (i < 5)
	{
		if ((all->txt[i].path))
			free(all->txt[i].path);
		if ((all->txt[i].img))
		{
			mlx_destroy_image(all->win.mlx, all->txt[i].img);
			all->txt[i].img = NULL;
		}
		if ((all->txt[i].addr))
			all->txt[i].addr = NULL;
		i++;
	}
}

void	ft_free_splt(char **map)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
	}
	free(map);
	map = NULL;
}
