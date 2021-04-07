/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:07 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:08 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_parser(char *file_cub, char mode)
{
	t_all	all;
	t_parse p;

	if (((p.fd = open(file_cub, O_RDONLY)) < 0) || (read(p.fd, 0, 0) < 0))
	{
		close(p.fd);
		ft_cub_error_exit(FILE_NOT_OPEN);
	}
	init_str(&all, mode);
	init_parse(&p);
	parse_config(&all, &p);
	ft_get_map(&all, &p);
	ft_store_map_to_struct(&all, &p);
	draw_screen(&all);
	return (0);
}

void	parse_config(t_all *all, t_parse *p)
{
	while (p->gnl && !p->flag)
	{
		p->gnl = get_next_line(p->fd, &p->line);
		if (*p->line == '\0')
		{
			ft_free_line(p->line);
			continue;
		}
		if ((ft_is_empty_line(p->line)))
		{
			if (ft_check_args(all, p) < 0)
				ft_parse_error(all, p, p->err);
			else
				continue;
		}
		get_arguments(all, p);
		ft_free_splt(p->splt_line);
		if (!p->flag)
			ft_free_line(p->line);
	}
	if (p->gnl <= 0)
	{
		ft_free_texture(all);
		ft_cub_error_exit(MAP_MISS);
	}
}

void	get_arguments(t_all *all, t_parse *p)
{
	if (!(p->splt_line = ft_split(p->line, ' ')))
		ft_parse_error(all, p, MEM_ERROR);
	if (ft_strncmp(p->splt_line[0], "NO", 3) == 0 ||
			ft_strncmp(p->splt_line[0], "SO", 3) == 0 ||
			ft_strncmp(p->splt_line[0], "WE", 3) == 0 ||
			ft_strncmp(p->splt_line[0], "EA", 3) == 0 ||
			ft_strncmp(p->splt_line[0], "S", 2) == 0)
		ft_get_texture(p->splt_line, all, p);
	else if (ft_strncmp(p->splt_line[0], "F", 2) == 0 ||
		ft_strncmp(p->splt_line[0], "C", 2) == 0)
		ft_get_color(p->splt_line, all, p);
	else if (ft_strncmp(p->splt_line[0], "R", 2) == 0)
		ft_get_resolution(p->splt_line, all, p);
	else
		ft_check_args(all, p);
	if (p->err < 0)
	{
		ft_free_splt(p->splt_line);
		ft_parse_error(all, p, p->err);
	}
}

void	init_str(t_all *all, int mode)
{
	all->scrnshoot = mode;
	all->win.height = 0;
	all->win.width = 0;
	all->txt[0].path = NULL;
	all->txt[1].path = NULL;
	all->txt[2].path = NULL;
	all->txt[3].path = NULL;
	all->txt[4].path = NULL;
	all->win.ceil_c = -1;
	all->win.floor_c = -1;
	all->num_sprites = 0;
	all->dist_buf = NULL;
	all->sprite = NULL;
	all->key.up = 0;
	all->key.down = 0;
	all->key.right = 0;
	all->key.left = 0;
	all->key.rot_right = 0;
	all->key.rot_left = 0;
}

void	init_parse(t_parse *p)
{
	p->flag = 0;
	p->gnl = 1;
	p->err = 0;
	p->x = 0;
	p->k = 0;
	p->screen_w = 0;
	p->screen_h = 0;
	p->plr_count = 0;
	p->str_count = 0;
	p->max_len = 0;
	p->line = NULL;
	p->splt_line = NULL;
	p->str = "\0";
	p->tmp = "\0";
}
