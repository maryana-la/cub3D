/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_get_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:48 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:49 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_get_resolution(char **file, t_all *all, t_parse *p)
{
	p->i = 0;
	if ((!file[1] || !file[2] || file[3]) || all->win.height || all->win.width)
		return ((p->err = RESOL_ERROR));
	while (++p->i < 3)
	{
		p->j = -1;
		while (file[p->i][++p->j] != '\0')
		{
			if (!(ft_isdigit(file[p->i][p->j])))
				return ((p->err = RESOL_ERROR));
		}
	}
	all->win.width = ft_atoi_cub(file[1]);
	all->win.height = ft_atoi_cub(file[2]);
	if (all->scrnshoot == 0)
	{
		mlx_get_screen_size(&p->screen_w, &p->screen_h);
		if (all->win.width > p->screen_w)
			all->win.width = p->screen_w;
		if (all->win.height > p->screen_h)
			all->win.height = p->screen_h;
	}
	if (all->win.height < 1 || all->win.width < 1)
		return (p->err = RESOL_ERROR);
	return (1);
}

int		ft_get_wall_txt(char **file, t_all *all, t_parse *p)
{
	if (file[0][0] == 'N' && file[0][1] == 'O' && all->txt[0].path == 0)
	{
		if (!(all->txt[0].path = ft_strdup(file[1])))
			return (p->err = MEM_ERROR);
	}
	else if (file[0][0] == 'S' && file[0][1] == 'O' && all->txt[1].path == 0)
	{
		if (!(all->txt[1].path = ft_strdup(file[1])))
			return (p->err = MEM_ERROR);
	}
	else if (file[0][0] == 'E' && file[0][1] == 'A' && all->txt[2].path == 0)
	{
		if (!(all->txt[2].path = ft_strdup(file[1])))
			return (p->err = MEM_ERROR);
	}
	else if (file[0][0] == 'W' && file[0][1] == 'E' && all->txt[3].path == 0)
	{
		if (!(all->txt[3].path = ft_strdup(file[1])))
			return (p->err = MEM_ERROR);
	}
	else
		return (p->err = PARAM_ERROR);
	return (1);
}

int		ft_get_texture(char **file, t_all *all, t_parse *p)
{
	if (!file[0] || !file[1] || file[2])
		return (p->err = TXT_INFO);
	if (!ft_check_extension(file[1], ".xpm") &&
		!ft_check_extension(file[1], ".png"))
		return (p->err = TXT_FILE);
	if (!(ft_strncmp(file[0], "S", 2)) && all->txt[4].path == 0)
	{
		if (!(all->txt[4].path = ft_strdup(file[1])))
			return (p->err = MEM_ERROR);
	}
	else
		return (ft_get_wall_txt(file, all, p));
	return (1);
}

int		ft_get_rgb(char **rgb, char **file, t_all *all, t_parse *p)
{
	if (!(rgb[0] && rgb[1] && rgb[2]))
	{
		ft_free_splt(rgb);
		return (p->err = COLOR_ERROR);
	}
	if ((ft_atoi_cub(rgb[0])) > 255 || (ft_atoi_cub(rgb[1])) > 255
		|| (ft_atoi_cub(rgb[2])) > 255)
	{
		ft_free_splt(rgb);
		return (p->err = COLOR_ERROR);
	}
	if (file[0][0] == 'F' && all->win.floor_c == (unsigned int)-1)
		all->win.floor_c = ((ft_atoi_cub(rgb[0]) & 0xff) << 16) +
			((ft_atoi_cub(rgb[1]) & 0xff) << 8) + (ft_atoi_cub(rgb[2]) & 0xff);
	else if (file[0][0] == 'C' && all->win.ceil_c == (unsigned int)-1)
		all->win.ceil_c = ((ft_atoi_cub(rgb[0]) & 0xff) << 16) +
			((ft_atoi_cub(rgb[1]) & 0xff) << 8) + (ft_atoi_cub(rgb[2]) & 0xff);
	else
	{
		ft_free_splt(rgb);
		return (p->err = COLOR_ERROR);
	}
	ft_free_splt(rgb);
	return (1);
}

int		ft_get_color(char **file, t_all *all, t_parse *p)
{
	int		count;
	char	**rgb;

	p->i = -1;
	count = 0;
	if (!file[0] || !file[1] || file[2])
		return (p->err = COLOR_ERROR);
	while (file[1][++p->i] != '\0')
	{
		if (ft_isdigit(file[1][p->i]) == 0)
		{
			if (file[1][p->i] == ',')
				count++;
			else
				return (p->err = COLOR_S_ERROR);
		}
	}
	if (count != 2)
		return (p->err = COLOR_S_ERROR);
	if (!(rgb = ft_split(file[1], ',')))
		return (p->err = MEM_ERROR);
	return (ft_get_rgb(rgb, file, all, p));
}
