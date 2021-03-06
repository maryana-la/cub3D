/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 20:50:52 by rchelsea          #+#    #+#             */
/*   Updated: 2021/01/03 18:42:57 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 48
# endif

int		get_next_line(int fd, char **line);
int		error_free (char **s1, char **s2);
int		return_value(int bytes_read, char **search_n, char **buffer);
char	*ft_strdup(char *s1);
char	*ft_strchr(char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strzero(size_t size);
char	*ft_strmove(char *ddst, char *ssrc, size_t len);
char	*check_rest(char **rest, char **line);
size_t	ft_strlen(char *s);

#endif
