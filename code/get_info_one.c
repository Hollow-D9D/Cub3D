/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:53:49 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:55:27 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		ft_take_num(const char *line, int *i)
{
	int num;

	num = 0;
	while (ft_isspace(line[*i]))
		(*i)++;
	while (ft_isdigit(line[*i]))
	{
		num = num * 10 + (line[*i] - '0');
		(*i)++;
	}
	while (ft_isspace(line[*i]))
		(*i)++;
	return (num);
}

int		ft_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int		ft_parse_map(char *line, t_args *info, int x)
{
	int y;
	int i;

	i = 0;
	y = 0;
	if (!ft_ini_map(line, info, x))
		return (0);
	x = 0;
	while (info->map[x])
	{
		while (line[i] && line[i] != '\n')
		{
			info->map[x][y] = line[i];
			i++;
			y++;
		}
		i++;
		info->map[x][y] = '\0';
		y = 0;
		x++;
	}
	free(line);
	return (1);
}

void	ft_clear_args(t_args *args)
{
	args->height = 0;
	args->width = 0;
	args->no = 0;
	args->so = 0;
	args->we = 0;
	args->ea = 0;
	args->sp = 0;
	args->f_color = 0;
	args->c_color = 0;
	args->map = 0;
}

int		ft_ini_map(const char *line, t_args *info, int x)
{
	int y;
	int i;
	int j;

	line = ft_strjoin(line, "\n");
	j = 0;
	i = 0;
	y = 0;
	if (!(info->map = malloc(sizeof(char*) * (x + 1))))
		return (0);
	while (y < x)
	{
		j++;
		if (line[i] == '\n')
		{
			if (!(info->map[y] = malloc(sizeof(char) * j)))
				return (0);
			j = 0;
			y++;
		}
		i++;
	}
	info->map[y] = NULL;
	return (1);
}
