/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rchelsea <rchelsea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 14:55:02 by rchelsea          #+#    #+#             */
/*   Updated: 2021/04/07 14:55:03 by rchelsea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_is_empty_line(char *line)
{
	int i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '\0')
		return (1);
	else
		return (0);
}

char	*ft_strjoin_n(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 2);
	if (!(new))
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\n';
	new[i + j + 1] = '\0';
	return (new);
}

int		ft_check_set(char c, char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int		ft_check_extension(char *file, char *end)
{
	int len_file;
	int len_end;

	len_file = ft_strlen(file) - 1;
	len_end = ft_strlen(end) - 1;
	if (len_file <= len_end)
		return (0);
	while (len_end >= 0)
	{
		if (file[len_file] != end[len_end])
			return (0);
		len_file--;
		len_end--;
	}
	return (1);
}

int		ft_check_args(t_all *all, t_parse *p)
{
	if (all->win.width && all->win.height && all->txt[0].path
		&& all->txt[1].path && all->txt[2].path && all->txt[3].path
		&& all->txt[4].path && (all->win.floor_c != (unsigned int)-1)
		&& all->win.ceil_c != (unsigned int)-1)
	{
		p->flag = 1;
		return (1);
	}
	return (p->err = PARAM_ERROR);
}
