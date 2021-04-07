/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:11 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 15:10:27 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_screen(t_all *all)
{
	all->win.mlx = mlx_init();
	if (all->scrnshoot == 0)
		if (!(all->win.win = mlx_new_window(all->win.mlx,
			all->win.width, all->win.height, "Cub3D")))
			ft_img_error_exit(all, MLX_ERR);
	if (!(all->dist_buf = malloc(sizeof(double) * all->win.width)))
		ft_img_error_exit(all, MEM_ERROR);
	init_textures(all);
	ft_render(all);
	if (all->scrnshoot == 1)
	{
		ft_bmp_init(all);
		exit(1);
	}
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	ft_cub_hook(all);
}

void	ft_render(t_all *all)
{
	int x;

	all->win.img = mlx_new_image(all->win.mlx, all->win.width, all->win.height);
	if (!(all->win.img))
		ft_img_error_exit(all, MLX_ERR);
	all->win.img_addr = mlx_get_data_addr(all->win.img, &all->win.bpp,
		&all->win.size_l, &all->win.endian);
	if (!(all->win.img_addr))
		ft_img_error_exit(all, IMG_ADDR);
	x = -1;
	while (++x < all->win.width)
	{
		cast_rays(all, x);
		all->dist_buf[x] = all->eng.wall_dist;
		ft_draw_wall(all, x);
		draw_ceiling_floor(all, x);
	}
	if (all->num_sprites > 0)
		cast_sprites(all);
}

void	cast_rays(t_all *all, int x)
{
	all->eng.cam_x = 2.0f * x / (double)all->win.width - 1.0f;
	all->eng.r_vec_x = all->eng.vec_x + all->eng.pln_x * all->eng.cam_x;
	all->eng.r_vec_y = all->eng.vec_y + all->eng.pln_y * all->eng.cam_x;
	all->eng.pl_x = (int)all->eng.pos_x;
	all->eng.pl_y = (int)all->eng.pos_y;
	all->eng.delta_x = fabs(1 / all->eng.r_vec_x);
	all->eng.delta_y = fabs(1 / all->eng.r_vec_y);
	all->eng.hit = 0;
	ft_get_side_dist(all);
	ft_dda(all);
	all->eng.line_h = (int)(all->win.width * 0.75 / all->eng.wall_dist);
	all->eng.draw_start = -all->eng.line_h / 2 + all->win.height / 2;
	if (all->eng.draw_start < 0)
		all->eng.draw_start = 0;
	all->eng.draw_end = all->eng.line_h / 2 + all->win.height / 2;
	if (all->eng.draw_end >= all->win.height)
		all->eng.draw_end = all->win.height;
	if (all->eng.side == 0)
		all->eng.wall = all->eng.pos_y + all->eng.wall_dist * all->eng.r_vec_y;
	else
		all->eng.wall = all->eng.pos_x + all->eng.wall_dist * all->eng.r_vec_x;
	all->eng.wall -= floor((all->eng.wall));
}

void	ft_get_side_dist(t_all *all)
{
	if (all->eng.r_vec_x < 0)
	{
		all->eng.step_x = -1;
		all->eng.side_dist_x = (all->eng.pos_x - all->eng.pl_x) *
			all->eng.delta_x;
	}
	else
	{
		all->eng.step_x = 1;
		all->eng.side_dist_x = (all->eng.pl_x + 1.0 - all->eng.pos_x) *
			all->eng.delta_x;
	}
	if (all->eng.r_vec_y < 0)
	{
		all->eng.step_y = -1;
		all->eng.side_dist_y = (all->eng.pos_y - all->eng.pl_y) *
			all->eng.delta_y;
	}
	else
	{
		all->eng.step_y = 1;
		all->eng.side_dist_y = (all->eng.pl_y + 1.0 - all->eng.pos_y) *
			all->eng.delta_y;
	}
}

void	ft_dda(t_all *all)
{
	while (all->eng.hit == 0)
	{
		if (all->eng.side_dist_x < all->eng.side_dist_y)
		{
			all->eng.side_dist_x += all->eng.delta_x;
			all->eng.pl_x += all->eng.step_x;
			all->eng.side = 0;
		}
		else
		{
			all->eng.side_dist_y += all->eng.delta_y;
			all->eng.pl_y += all->eng.step_y;
			all->eng.side = 1;
		}
		if (all->map[all->eng.pl_x][all->eng.pl_y] == '1')
			all->eng.hit = 1;
	}
	if (all->eng.side == 0)
		all->eng.wall_dist = (double)(all->eng.pl_x - all->eng.pos_x +
			(1 - all->eng.step_x) / 2) / all->eng.r_vec_x;
	else
		all->eng.wall_dist = (double)(all->eng.pl_y - all->eng.pos_y +
			(1 - all->eng.step_y) / 2) / all->eng.r_vec_y;
}
