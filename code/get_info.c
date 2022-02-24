/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:53:07 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:58:04 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int			ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' ||
			c == '\v' || c == '\f' || c == ' ')
		return (1);
	return (0);
}

int			give_r(t_args *info, const char *line, int i)
{
	i++;
	info->width = ft_take_num(line, &i);
	info->height = ft_take_num(line, &i);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (info->height > 0 && info->width > 0);
}

int			give_color(t_args *info, const char *line, int i, char c)
{
	int r;
	int g;
	int b;

	i++;
	r = ft_take_num(line, &i);
	if (line[i++] != ',')
		return (0);
	g = ft_take_num(line, &i);
	if (line[i++] != ',')
		return (0);
	b = ft_take_num(line, &i);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	if (c == 'C')
		return (info->c_color = ft_trgb(0, r, g, b));
	else
		return (info->f_color = ft_trgb(0, r, g, b));
}

static int	give_key(t_args *info, const char *line, int i)
{
	if (line)
	{
		if (line[i] == 'R')
			return (give_r(info, line, i));
		else if (line[i] == 'C')
			return (give_color(info, line, i, 'C'));
		else if (line[i] == 'F')
			return (give_color(info, line, i, 'F'));
		else if (line[i] == 'N' && line[i + 1] == 'O')
			return (give_no(info, line, i));
		else if (line[i] == 'S' && line[i + 1] == 'O')
			return (give_so(info, line, i));
		else if (line[i] == 'W' && line[i + 1] == 'E')
			return (give_we(info, line, i));
		else if (line[i] == 'E' && line[i + 1] == 'A')
			return (give_ea(info, line, i));
		else if (line[i] == 'S')
			return (give_s(info, line, i));
		else
			return (0);
	}
	return (0);
}

int			getinfo(t_args *info, int fd, void *mlx, int *i)
{
	char	*tmp;
	char	*buff;

	while ((i[1] = ft_get_next_line(fd, &tmp) > 0))
	{
		i[0] = 0;
		if (!tmp[0])
			continue ;
		while (ft_isspace(tmp[i[0]]))
			i[0]++;
		if (tmp[i[0]] == '1')
			break ;
		if (!give_key(info, tmp, i[0]))
			return (ft_error("Error\nParsing error"));
		free(tmp);
	}
	if (i[1] > 0 && (i[1] = 1))
		buff = ft_strdup(tmp);
	else
		return (ft_error("Error\nNo map"));
	while (ft_get_next_line(fd, &tmp))
		buff = ft_app_line(&i[1], buff, tmp);
	buff = ft_app_line(&i[1], buff, tmp);
	ft_parse_map(buff, info, i[1]);
	return (ft_check_info(info, mlx));
}
