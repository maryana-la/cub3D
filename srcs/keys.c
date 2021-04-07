/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:39 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:40 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		move(t_all *all)
{
	if ((all->key.up == 1) || (all->key.down == 1))
		ft_move_vertical(all);
	if ((all->key.left == 1) || (all->key.right == 1))
		ft_move_horizontal(all);
	if ((all->key.rot_right == 1) || (all->key.rot_left == 1))
		ft_rotate(all);
	ft_render(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);
	return (0);
}

void	ft_move_vertical(t_all *all)
{
	int ch_y;
	int ch_x;

	if (all->key.up == 1)
	{
		ch_x = (int)(all->eng.pos_x + all->eng.vec_x * MOVE_SP);
		ch_y = (int)(all->eng.pos_y + all->eng.vec_y * MOVE_SP);
		if (all->map[ch_x][(int)(all->eng.pos_y)] == '0')
			all->eng.pos_x += (all->eng.vec_x * MOVE_SP);
		if (all->map[(int)(all->eng.pos_x)][ch_y] == '0')
			all->eng.pos_y += (all->eng.vec_y * MOVE_SP);
	}
	if (all->key.down == 1)
	{
		ch_x = (int)(all->eng.pos_x - all->eng.vec_x * MOVE_SP);
		ch_y = (int)(all->eng.pos_y - all->eng.vec_y * MOVE_SP);
		if (all->map[ch_x][(int)(all->eng.pos_y)] == '0')
			all->eng.pos_x -= all->eng.vec_x * MOVE_SP;
		if (all->map[(int)(all->eng.pos_x)][ch_y] == '0')
			all->eng.pos_y -= all->eng.vec_y * MOVE_SP;
	}
}

void	ft_move_horizontal(t_all *all)
{
	int ch_y;
	int ch_x;

	if (all->key.left == 1)
	{
		ch_x = (int)(all->eng.pos_x - all->eng.vec_y * MOVE_SP);
		ch_y = (int)(all->eng.pos_y + all->eng.vec_x * MOVE_SP);
		if (all->map[ch_x][(int)(all->eng.pos_y)] == '0')
			all->eng.pos_x -= all->eng.vec_y * MOVE_SP;
		if (all->map[(int)(all->eng.pos_x)][ch_y] == '0')
			all->eng.pos_y += all->eng.vec_x * MOVE_SP;
	}
	if (all->key.right == 1)
	{
		ch_x = (int)(all->eng.pos_x + all->eng.vec_y * MOVE_SP);
		ch_y = (int)(all->eng.pos_y - all->eng.vec_x * MOVE_SP);
		if (all->map[ch_x][(int)(all->eng.pos_y)] == '0')
			all->eng.pos_x += all->eng.vec_y * MOVE_SP;
		if (all->map[(int)(all->eng.pos_x)][ch_y] == '0')
			all->eng.pos_y -= all->eng.vec_x * MOVE_SP;
	}
}

void	ft_rotate(t_all *all)
{
	double pr_vecx;
	double pr_plnx;

	pr_vecx = all->eng.vec_x;
	pr_plnx = all->eng.pln_x;
	if (all->key.rot_right == 1)
	{
		all->eng.vec_x = all->eng.vec_x * cos(-ROTATE) -
			all->eng.vec_y * sin(-ROTATE);
		all->eng.vec_y = pr_vecx * sin(-ROTATE) + all->eng.vec_y * cos(-ROTATE);
		all->eng.pln_x = all->eng.pln_x * cos(-ROTATE) -
			all->eng.pln_y * sin(-ROTATE);
		all->eng.pln_y = pr_plnx * sin(-ROTATE) + all->eng.pln_y * cos(-ROTATE);
	}
	if (all->key.rot_left == 1)
	{
		all->eng.vec_x = all->eng.vec_x * cos(ROTATE) -
			all->eng.vec_y * sin(ROTATE);
		all->eng.vec_y = pr_vecx * sin(ROTATE) + all->eng.vec_y * cos(ROTATE);
		all->eng.pln_x = all->eng.pln_x * cos(ROTATE) -
			all->eng.pln_y * sin(ROTATE);
		all->eng.pln_y = pr_plnx * sin(ROTATE) + all->eng.pln_y * cos(ROTATE);
	}
}
