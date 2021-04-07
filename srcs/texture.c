/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:23 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:24 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init_textures(t_all *all)
{
	int i;
	int	fd;

	i = -1;
	while (++i < 5)
	{
		if ((fd = open(all->txt[i].path, O_RDONLY) < 0) || (read(fd, 0, 0) < 0))
			ft_img_error_exit(all, TXT_FILE);
		close(fd);
		if ((ft_check_extension(all->txt[i].path, ".xpm")))
			all->txt[i].img = mlx_xpm_file_to_image(all->win.mlx,
				all->txt[i].path, &all->txt[i].width, &all->txt[i].hight);
		else if ((ft_check_extension(all->txt[i].path, ".png")))
			all->txt[i].img = mlx_png_file_to_image(all->win.mlx,
				all->txt[i].path, &all->txt[i].width, &all->txt[i].hight);
		else
			ft_img_error_exit(all, TXT_FILE);
		if (!(all->txt[i].img))
			ft_img_error_exit(all, TXT_FILE);
		if (!(all->txt[i].addr = mlx_get_data_addr(all->txt[i].img,
			&all->txt[i].bpp, &all->txt[i].lin_l, &all->txt[i].endian)))
			ft_img_error_exit(all, TXT_ADDR);
	}
}

void			ft_draw_wall(t_all *all, int x)
{
	if (all->eng.side == 0)
	{
		if (all->eng.step_x > 0)
			apply_texture(all, all->txt[0], x);
		else if (all->eng.step_x < 0)
			apply_texture(all, all->txt[1], x);
	}
	if (all->eng.side == 1)
	{
		if (all->eng.step_y > 0)
			apply_texture(all, all->txt[3], x);
		else if (all->eng.step_y < 0)
			apply_texture(all, all->txt[2], x);
	}
}

void			apply_texture(t_all *all, t_texture txt, int x)
{
	int i;
	int color;

	i = all->eng.draw_start;
	txt.txt_x = (int)(all->eng.wall * (double)txt.width);
	if (all->eng.side == 0 && all->eng.r_vec_x > 0)
		txt.txt_x = txt.width - txt.txt_x - 1;
	if (all->eng.side == 1 && all->eng.r_vec_y < 0)
		txt.txt_x = txt.width - txt.txt_x - 1;
	txt.step = 1.0 * txt.hight / all->eng.line_h;
	txt.pos = (all->eng.draw_start - all->win.height / 2 +
		all->eng.line_h / 2) * txt.step;
	while (i < all->eng.draw_end)
	{
		txt.txt_y = (int)txt.pos & (txt.hight - 1);
		txt.pos += txt.step;
		color = my_mlx_pixel_take(&txt, txt.txt_x, txt.txt_y);
		my_mlx_pixel_put(all, x, i, color);
		i++;
	}
}

unsigned int	my_mlx_pixel_take(t_texture *txt, int x, int y)
{
	char			*addr;
	unsigned int	color;

	addr = txt->addr + (y * txt->lin_l + x * (txt->bpp / 8));
	color = *(unsigned int*)addr;
	return (color);
}

void			my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*dst;

	dst = all->win.img_addr + (y * all->win.size_l + x * (all->win.bpp / 8));
	*(unsigned int*)dst = color;
}
