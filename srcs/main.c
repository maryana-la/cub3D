/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:43 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:44 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cub_hook(t_all *all)
{
	mlx_hook(all->win.win, KEYPRESS, (1L << 0), &key_press, all);
	mlx_hook(all->win.win, KEYRELEASE, (1L << 1), &key_release, all);
	mlx_hook(all->win.win, WIN_DESTROY, 0, &cross_press, all);
	mlx_loop_hook(all->win.mlx, move, all);
	mlx_loop(all->win.mlx);
}

int		key_press(int keycode, t_all *all)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		all->key.up = 1;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		all->key.down = 1;
	if (keycode == KEY_A)
		all->key.left = 1;
	if (keycode == KEY_D)
		all->key.right = 1;
	if (keycode == KEY_RIGHT)
		all->key.rot_right = 1;
	if (keycode == KEY_LEFT)
		all->key.rot_left = 1;
	if (keycode == KEY_ESC)
		all->key.esc = 1;
	return (0);
}

int		key_release(int keycode, t_all *all)
{
	if (keycode == KEY_W || keycode == KEY_UP)
		all->key.up = 0;
	if (keycode == KEY_S || keycode == KEY_DOWN)
		all->key.down = 0;
	if (keycode == KEY_A)
		all->key.left = 0;
	if (keycode == KEY_D)
		all->key.right = 0;
	if (keycode == KEY_RIGHT)
		all->key.rot_right = 0;
	if (keycode == KEY_LEFT)
		all->key.rot_left = 0;
	if (keycode == KEY_ESC)
		ft_cub_exit(all);
	return (0);
}

int		cross_press(t_all *all)
{
	ft_cub_exit(all);
	return (0);
}

int		main(int argc, char **argv)
{
	int	scrnsht;

	scrnsht = 0;
	if (argc < 2 || argc > 3)
		ft_cub_error_exit(ARGS_AMOUNT);
	else if (argc == 2 || argc == 3)
	{
		if (ft_check_extension(argv[1], ".cub") == 0)
			ft_cub_error_exit(FILE_ERROR);
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 7) != 0)
				ft_cub_error_exit(ARGS_INVALID);
			scrnsht = 1;
		}
		ft_parser(argv[1], scrnsht);
	}
	return (0);
}
