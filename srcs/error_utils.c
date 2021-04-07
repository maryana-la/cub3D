/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:54:00 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:54:03 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_parse_err_print(int err)
{
	if (err == FILE_ERROR)
		printf("Error\nFile extension is not valid\n");
	else if (err == FILE_NOT_OPEN)
		printf("Error\nCannot open file\n");
	else if (err == ARGS_AMOUNT)
		printf("Error\nWrong amount of arguments\n");
	else if (err == ARGS_INVALID)
		printf("Error\nInvalid arguments\n");
	else if (err == MEM_ERROR)
		printf("Error\nFailed to allocate memory\n");
	else if (err == TXT_FILE)
		printf("Error\nWrong texture file\n");
	else if (err == TXT_INFO)
		printf("Error\nWrong texture information\n");
	else if (err == RESOL_ERROR)
		printf("Error\nWrong resolution information\n");
	else if (err == COLOR_ERROR)
		printf("Error\nWrong color information\n");
	else if (err == COLOR_S_ERROR)
		printf("Error\nWrong symbols in color\n");
	else if (err == PARAM_ERROR)
		printf("Error\nWrong parameters\n");
}

static void	ft_map_err_print(int err)
{
	if (err == MAP_SYMBOLS)
		printf("Error\nBad map. Wrong symbols in map\n");
	else if (err == MAP_PLAYER)
		printf("Error\nBad map. Wrong amount of players\n");
	else if (err == MAP_EMP_LINE)
		printf("Error\nBad map. Empty line in map\n");
	else if (err == MAP_PERIM)
		printf("Error\nBad map. Check perimeter\n");
	else if (err == MAP_HOLES)
		printf("Error\nBad map. Check holes\n");
	else if (err == MAP_MISS)
		printf("Error\nBad map. Map is missing or too short\n");
	else if (err == IMG_ADDR)
		printf("Error\nCannot get image address\n");
	else if (err == TXT_ADDR)
		printf("Error\nCannot get texture address\n");
	else if (err == MLX_ERR)
		printf("Error\nFailed to open new window\n");
	else if (err == BMP_ERR)
		printf("Error\nCannot create BMP file\n");
}

void		ft_print_error(int err)
{
	if (err > -12)
		ft_parse_err_print(err);
	else if (err <= -12)
		ft_map_err_print(err);
}

void		ft_free_line(char *line)
{
	if ((line))
	{
		free(line);
		line = NULL;
	}
}

void		ft_free_map(char **map, int len)
{
	int		i;

	i = -1;
	while (map[++i] && i < len)
	{
		if (map[i])
		{
			free(map[i]);
			map[i] = NULL;
		}
	}
	free(map);
	map = NULL;
}
