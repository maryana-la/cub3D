/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_map_get_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:52 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:53 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_map(t_all *all, t_parse *p)
{
	ft_get_map_line(all, p, -1);
	if (!(p->str = ft_strjoin_n(p->str, p->line)))
		ft_parse_error(all, p, MEM_ERROR);
	ft_free_line(p->line);
	while (p->gnl)
	{
		p->gnl = get_next_line(p->fd, &p->line);
		ft_get_map_line(all, p, -1);
		p->tmp = p->str;
		if (!(p->str = ft_strjoin_n(p->str, p->line)))
		{
			ft_free_line(p->tmp);
			ft_parse_error(all, p, MEM_ERROR);
		}
		ft_free_line(p->tmp);
		ft_free_line(p->line);
	}
	close(p->fd);
	if (p->plr_count != 1)
		ft_map_parse_error(all, MAP_PLAYER);
	p->dlina_str = ft_strlen(p->str);
	while (p->str[--p->dlina_str] == '\n')
		p->str_count--;
}

void	ft_get_map_line(t_all *all, t_parse *p, int j)
{
	while (p->line[++j])
	{
		if ((ft_check_set(p->line[j], "NSWE")))
		{
			ft_set_camera(p->line[j], p->str_count, j, all);
			p->line[j] = '0';
			p->plr_count++;
		}
		if (p->line[j] == '2')
			all->num_sprites++;
		else if (!(ft_check_set(p->line[j], " 012NSWE")))
			ft_parse_error(all, p, MAP_SYMBOLS);
	}
	if (p->max_len < (int)ft_strlen(p->line))
		p->max_len = (int)ft_strlen(p->line);
	p->str_count++;
}

void	ft_set_camera_we(char c, t_all *all)
{
	if (c == 'W')
	{
		all->eng.vec_x = 0.001;
		all->eng.vec_y = -1.0;
		all->eng.pln_x = -0.80;
		all->eng.pln_y = 0.001;
	}
	else if (c == 'E')
	{
		all->eng.vec_x = 0.001;
		all->eng.vec_y = 1.0;
		all->eng.pln_x = 0.80;
		all->eng.pln_y = 0.001;
	}
}

void	ft_set_camera(char c, int i, int j, t_all *all)
{
	all->eng.pos_x = i + 0.5;
	all->eng.pos_y = j + 0.5;
	if (c == 'N')
	{
		all->eng.vec_x = -1.0;
		all->eng.vec_y = 0.001;
		all->eng.pln_x = 0.001;
		all->eng.pln_y = 0.80;
	}
	else if (c == 'S')
	{
		all->eng.vec_x = 1.0;
		all->eng.vec_y = 0.001;
		all->eng.pln_x = 0.001;
		all->eng.pln_y = -0.80;
	}
	else
		ft_set_camera_we(c, all);
}

void	ft_set_sprite(int i, int j, int spr_count, t_all *all)
{
	all->sprite[spr_count].x = i + 0.5f;
	all->sprite[spr_count].y = j + 0.5f;
}
