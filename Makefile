# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/07 14:58:28 by rchelsea          #+#    #+#              #
#    Updated: 2021/04/07 16:16:54 by rchelsea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC :=	srcs/main.c srcs/bmp.c srcs/error_utils.c srcs/error.c srcs/exit.c \
		srcs/keys.c srcs/parcer_get_args.c \
		srcs/parcer_map_get.c srcs/parcer_utils.c srcs/parcer.c srcs/raycast.c \
		srcs/sprite.c srcs/texture.c srcs/parcer_map_get_utils.c \
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c \
		utils/ft_atoi.c utils/ft_isdigit.c utils/ft_strncmp.c \
		utils/ft_strtrim.c utils/ft_split.c \
		utils/ft_calloc.c utils/ft_memset.c

OBJ := ${SRC:.c=.o}

HEADERS = mlx/mlx.h get_next_line/get_next_line.h srcs/cub3d.h

LIBS = mlx/libmlx.a -lz -framework OpenGl -framework AppKit 

MLX	= mlx/libmlx.a

%.o : %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(MLX) $(OBJ) 
	$(CC) $(CFLAGS) $(LIBS) $(OBJ) -o $(NAME)

$(MLX):
	$(MAKE) -C mlx

bonus: all

clean:
	rm -f $(OBJ)

fclean: clean
	make clean -C mlx/
	rm -f $(NAME)

re: fclean all

.PHONY:	all clean fclean re
