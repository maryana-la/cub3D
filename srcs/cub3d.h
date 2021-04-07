/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:53:08 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:57:41 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>
# include "../mlx/mlx.h"
# include "../get_next_line/get_next_line.h"

# define KEYPRESS		2
# define KEYRELEASE		3
# define WIN_DESTROY	17
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define KEY_Q			12
# define KEY_W			13
# define KEY_E			14
# define KEY_R			15
# define KEY_ESC		53
# define KEY_LEFT		123
# define KEY_RIGHT		124
# define KEY_DOWN		125
# define KEY_UP			126

# define MOVE_SP		0.2f
# define ROTATE			0.09f

# define FILE_ERROR		-1
# define FILE_NOT_OPEN	-2
# define ARGS_AMOUNT	-3
# define ARGS_INVALID	-4
# define MEM_ERROR		-5
# define TXT_FILE		-6
# define TXT_INFO		-7
# define RESOL_ERROR	-8
# define COLOR_ERROR	-9
# define COLOR_S_ERROR	-10
# define PARAM_ERROR 	-11
# define MAP_SYMBOLS	-12
# define MAP_PLAYER		-13
# define MAP_EMP_LINE	-14
# define MAP_PERIM		-15
# define MAP_HOLES		-16
# define MAP_MISS		-17
# define IMG_ADDR		-18
# define TXT_ADDR		-19
# define MLX_ERR		-20
# define BMP_ERR		-21

typedef struct		s_parse
{
	char			*line;
	char			*str;
	char			*tmp;
	char			**splt_line;
	int				fd;
	int				flag;
	int				gnl;
	int				plr_count;
	int				str_count;
	int				dlina_str;
	int				max_len;
	int				err;
	int				screen_w;
	int				screen_h;
	int				x;
	int				y;
	int				k;
	int				i;
	int				j;
}					t_parse;

typedef struct		s_win
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*img_addr;
	int				size_l;
	int				bpp;
	int				endian;
	int				width;
	int				height;
	unsigned int	ceil_c;
	unsigned int	floor_c;
}					t_win;

typedef struct		s_engine
{
	double			pos_x;
	double			pos_y;
	double			vec_x;
	double			vec_y;
	double			pln_x;
	double			pln_y;
	double			cam_x;
	double			r_vec_x;
	double			r_vec_y;
	int				pl_x;
	int				pl_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_x;
	double			delta_y;
	double			wall_dist;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				line_h;
	int				draw_start;
	int				draw_end;
	double			wall;
}					t_engine;

typedef	struct		s_texture
{
	char			*path;
	void			*img;
	char			*addr;
	int				mode;
	int				width;
	int				hight;
	int				bpp;
	int				lin_l;
	int				endian;
	int				txt_x;
	int				txt_y;
	double			step;
	double			pos;
}					t_texture;

typedef	struct		s_eng_spr
{
	double			x;
	double			y;
	double			inv_det;
	double			trs_x;
	double			trs_y;
	int				screen;
	int				height;
	int				start_y;
	int				end_y;
	int				width;
	int				start_x;
	int				end_x;
	int				tex_x;
	int				tex_y;

}					t_eng_spr;

typedef struct		s_sprite
{
	double			x;
	double			y;
	double			dist;
}					t_sprite;

typedef	struct		s_keys
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				rot_left;
	int				rot_right;
	int				esc;
}					t_keys;

typedef	struct		s_bmp
{
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				size;
	int				fd;
}					t_bmp;

typedef	struct		s_all
{
	t_win			win;
	t_engine		eng;
	t_eng_spr		spr;
	t_texture		txt[5];
	t_sprite		*sprite;
	t_keys			key;
	int				num_sprites;
	double			*dist_buf;
	int				scrnshoot;
	char			**map;
}					t_all;

/*
**		main.c
*/

int					main(int argc, char **argv);
void				ft_cub_hook(t_all *all);
int					key_press(int keycode, t_all *all);
int					key_release(int keycode, t_all *all);
int					cross_press(t_all *all);

/*
**		parcer.c
*/

int					ft_parser(char *file_cub, char mode);
void				parse_config(t_all *all, t_parse *p);
void				get_arguments(t_all *all, t_parse *p);
void				init_str(t_all *all, int mode);
void				init_parse(t_parse *p);

/*
**		parcer_get_args.c
*/

int					ft_get_resolution(char **file, t_all *all, t_parse *p);
int					ft_get_wall_txt(char **file, t_all *all, t_parse *p);
int					ft_get_texture(char **file, t_all *all, t_parse *p);
int					ft_get_rgb(char **rgb, char **file, t_all *all, t_parse *p);
int					ft_get_color(char **file, t_all *all, t_parse *p);

/*
**		parcer_map_get.c
*/

void				ft_str_to_array(t_all *all, t_parse *p);
void				ft_store_map_to_struct(t_all *all, t_parse *p);
int					ft_verify_map(t_parse *p, char **map, int arr_len);
int					ft_check_inside_map(char **map, int i, int j);

/*
**		parcer_map_get_utils.c
*/

void				ft_get_map(t_all *all, t_parse *p);
void				ft_get_map_line(t_all *all, t_parse *p, int j);
void				ft_set_camera(char c, int i, int j, t_all *all);
void				ft_set_camera_we(char c, t_all *all);
void				ft_set_sprite(int i, int j, int spr_count, t_all *all);

/*
**		parcer_utils.c
*/

int					ft_is_empty_line(char *line);
char				*ft_strjoin_n(char *s1, char *s2);
int					ft_check_set(char c, char *line);
int					ft_check_extension(char *file, char *end);
int					ft_check_args(t_all *all, t_parse *p);

/*
**		keys.c
*/

int					move(t_all *all);
void				ft_move_vertical(t_all *all);
void				ft_move_horizontal(t_all *all);
void				ft_rotate(t_all *all);

/*
**		raycast.c
*/

void				draw_screen(t_all *all);
void				ft_render(t_all *all);
void				cast_rays(t_all *all, int x);
void				ft_get_side_dist(t_all *all);
void				ft_dda(t_all *all);

/*
**		sprite.c
*/

void				cast_sprites(t_all *all);
void				sort_sprites(t_all *all);
void				ft_sprite_dimension(t_all *all);
void				ft_draw_sprite(t_all *all);
void				draw_ceiling_floor(t_all *all, int x);

/*
**		texture.c
*/

void				init_textures(t_all *all);
void				ft_draw_wall(t_all *all, int x);
void				apply_texture(t_all *all, t_texture txt, int x);
unsigned int		my_mlx_pixel_take(t_texture *txt, int x, int y);
void				my_mlx_pixel_put(t_all *all, int x, int y, int color);

/*
** 		bmp.c
*/

void				ft_bmp_init(t_all *all);

/*
**		error.c
*/

void				ft_cub_error_exit(int error);
void				ft_img_error_exit(t_all *all, int err);
void				ft_parse_error(t_all *all, t_parse *p, int err);
void				ft_map_parse_error(t_all *all, int error);
void				ft_map_check_error(t_all *all, int x, int error);

/*
**		error_utils.c
*/

void				ft_print_error (int err);
void				ft_free_line(char *line);
void				ft_free_map(char **map, int len);

/*
**		exit.c
*/

void				ft_cub_exit(t_all *all);
void				ft_free_texture(t_all *all);
void				ft_free_splt(char **map);

/*
**		utils
*/

int					ft_atoi_cub(const char *str);
int					ft_isdigit(int c);
char				**ft_split(char const *s, char c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strtrim(char *s1, char *set);
void				*ft_memset(void *b, int c, size_t len);
void				*ft_calloc(size_t count, size_t size);

#endif
