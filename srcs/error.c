/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:07 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:08 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_cub_error_exit(int error)
{
	ft_print_error(error);
	exit(0);
}

void	ft_img_error_exit(t_all *all, int err)
{
	ft_print_error(err);
	ft_cub_exit(all);
}

void	ft_parse_error(t_all *all, t_parse *p, int err)
{
	ft_free_line(p->line);
	ft_free_texture(all);
	close(p->fd);
	ft_print_error(err);
	exit(0);
}

void	ft_map_parse_error(t_all *all, int error)
{
	ft_free_texture(all);
	ft_cub_error_exit(error);
}

void	ft_map_check_error(t_all *all, int x, int error)
{
	ft_free_texture(all);
	ft_free_map(all->map, x);
	ft_cub_error_exit(error);
}
