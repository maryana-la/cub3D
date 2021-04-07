/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:53:00 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:53:01 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_bmp_header_info(t_bmp *bmp, t_all *all, int i)
{
	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[2] = (unsigned char)(bmp->size);
	bmp->header[3] = (unsigned char)(bmp->size >> 8);
	bmp->header[4] = (unsigned char)(bmp->size >> 16);
	bmp->header[5] = (unsigned char)(bmp->size >> 24);
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[4] = (unsigned char)(all->win.width);
	bmp->info[5] = (unsigned char)(all->win.width >> 8);
	bmp->info[6] = (unsigned char)(all->win.width >> 16);
	bmp->info[7] = (unsigned char)(all->win.width >> 24);
	bmp->info[8] = (unsigned char)(all->win.height);
	bmp->info[9] = (unsigned char)(all->win.height >> 8);
	bmp->info[10] = (unsigned char)(all->win.height >> 16);
	bmp->info[11] = (unsigned char)(all->win.height >> 24);
	bmp->info[12] = 1;
	bmp->info[14] = 24;
}

static int	get_color(t_all *all, int x, int y)
{
	int	color;

	color = *(int*)(all->win.img_addr
			+ (4 * (int)all->win.width * ((int)all->win.height - 1 - y))
			+ (4 * x));
	return (color);
}

static void	draw_bmp(t_all *all, t_bmp *bmp)
{
	int i;
	int j;
	int color;

	j = -1;
	while (++j < all->win.height)
	{
		i = -1;
		while (++i < all->win.width)
		{
			color = get_color(all, i, j);
			write(bmp->fd, &color, 3);
		}
		i = -1;
		while (++i < (4 - (all->win.width * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
	}
}

void		ft_bmp_init(t_all *all)
{
	t_bmp	bmp;
	int		i;

	i = 0;
	bmp.size = 54 + (3 * (all->win.height * all->win.width));
	bmp.fd = open("img.bmp", O_CREAT | O_WRONLY, S_IRWXU | S_IROTH);
	if (bmp.fd < 0)
		ft_img_error_exit(all, BMP_ERR);
	set_bmp_header_info(&bmp, all, 0);
	while (i < 3)
		bmp.pad[i++] = 0;
	write(bmp.fd, bmp.header, 14);
	write(bmp.fd, bmp.info, 40);
	draw_bmp(all, &bmp);
	close(bmp.fd);
	ft_cub_exit(all);
}
