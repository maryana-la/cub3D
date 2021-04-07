/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:17 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:18 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cast_sprites(t_all *all)
{
	int i;

	i = -1;
	while (++i < all->num_sprites)
		all->sprite[i].dist = ((all->eng.pos_x - all->sprite[i].x) *
			(all->eng.pos_x - all->sprite[i].x) + (all->eng.pos_y -
			all->sprite[i].y) * (all->eng.pos_y - all->sprite[i].y));
	sort_sprites(all);
	i = -1;
	while (++i < all->num_sprites)
	{
		all->spr.x = all->sprite[i].x - all->eng.pos_x;
		all->spr.y = all->sprite[i].y - all->eng.pos_y;
		all->spr.inv_det = 1.0 /
			(all->eng.pln_x * all->eng.vec_y - all->eng.vec_x * all->eng.pln_y);
		all->spr.trs_x = all->spr.inv_det *
			(all->eng.vec_y * all->spr.x - all->eng.vec_x * all->spr.y);
		all->spr.trs_y = all->spr.inv_det *
			(-all->eng.pln_y * all->spr.x + all->eng.pln_x * all->spr.y);
		all->spr.screen = (int)(all->win.width / 2) *
			(1 + all->spr.trs_x / all->spr.trs_y);
		ft_sprite_dimension(all);
		ft_draw_sprite(all);
	}
}

void	sort_sprites(t_all *all)
{
	int			i;
	int			j;
	t_sprite	key;

	i = 1;
	while (i < all->num_sprites)
	{
		key = all->sprite[i];
		j = i - 1;
		while (j >= 0 && all->sprite[j].dist < key.dist)
		{
			all->sprite[j + 1] = all->sprite[j];
			j = j - 1;
		}
		all->sprite[j + 1] = key;
		i++;
	}
}

void	ft_sprite_dimension(t_all *all)
{
	all->spr.height = abs((int)(all->win.width * 0.75 / (all->spr.trs_y)));
	all->spr.width = abs((int)(all->win.width * 0.75 / (all->spr.trs_y)));
	all->spr.start_y = -all->spr.height / 2 + all->win.height / 2;
	if (all->spr.start_y < 0)
		all->spr.start_y = 0;
	all->spr.end_y = all->spr.height / 2 + all->win.height / 2;
	if (all->spr.end_y >= all->win.height)
		all->spr.end_y = all->win.height;
	all->spr.start_x = -all->spr.width / 2 + all->spr.screen;
	if (all->spr.start_x < 0)
		all->spr.start_x = 0;
	all->spr.end_x = all->spr.width / 2 + all->spr.screen;
	if (all->spr.end_x >= all->win.width)
		all->spr.end_x = all->win.width;
}

void	ft_draw_sprite(t_all *all)
{
	int x;
	int y;
	int color;

	x = all->spr.start_x - 1;
	while (++x < all->spr.end_x)
	{
		all->spr.tex_x = (int)(256 * (x - (-all->spr.width / 2 +
			all->spr.screen)) * all->txt[4].width / all->spr.width) / 256;
		if (all->spr.trs_y > 0 && x >= 0 && x < all->win.width &&
			all->spr.trs_y < all->dist_buf[x])
		{
			y = all->spr.start_y - 1;
			while (++y < all->spr.end_y)
			{
				all->spr.tex_y = ((all->spr.height * 128 - all->win.height *
					128 + y * 256) * all->txt[4].hight / all->spr.height) / 256;
				color = my_mlx_pixel_take(&all->txt[4],
					all->spr.tex_x, all->spr.tex_y);
				if (color > 0)
					my_mlx_pixel_put(all, x, y, color);
			}
		}
	}
}

void	draw_ceiling_floor(t_all *all, int x)
{
	int i;

	i = -1;
	while (++i < all->eng.draw_start)
		my_mlx_pixel_put(all, x, i, all->win.ceil_c);
	i = all->eng.draw_end;
	while (++i < all->win.height)
		my_mlx_pixel_put(all, x, i, all->win.floor_c);
}
