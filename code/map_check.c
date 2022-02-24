/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:58:51 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 00:57:47 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		ft_check_element(char **info, int i, int j, char c)
{
	if (c == 'H')
	{
		if (info[i][j] == ' ')
			return (ft_check_char(" 1", info[i][j - 1]));
		else if (info[i][j] == '1')
			return (1);
		else
			return (info[i][j - 1] != ' ' && info[i][j + 1]);
	}
	else
	{
		if (info[i][j] == ' ')
			return (ft_check_char(" 1", info[i - 1][j]));
		else if (info[i][j] == '1')
			return (1);
		else
			return (ft_check_char(" 012NSEW", info[i - 1][j]) &&
				info[i - 1][j] != ' ' && info[i + 1]);
	}
}

void	ft_check_borders(char **info, int *gotchar)
{
	int j;

	j = 0;
	while (info[0][j])
	{
		if (!ft_check_char(" 1", info[0][j]))
			*gotchar = 0;
		j++;
	}
	j = 0;
	while (info[j])
	{
		if (!ft_check_char(" 1", info[j][0]))
			*gotchar = 0;
		j++;
	}
}

int		ft_check_map(t_args *info)
{
	int i;
	int j;
	int gotchar;

	gotchar = 0;
	i = 0;
	while (info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if (ft_check_char("NSEW", info->map[i][j]))
				gotchar++;
			if (!(ft_check_char(" 012NSEW", info->map[i][j])) || gotchar > 1)
				ft_error("Error\nForbidden symbol in the map");
			if (j && !ft_check_element(info->map, i, j, 'H'))
				ft_error("Error\nMap error horizontal part");
			if (i && !ft_check_element(info->map, i, j, 'V'))
				ft_error("Error\nMap error vertical part");
			j++;
		}
		i++;
	}
	ft_check_borders(info->map, &gotchar);
	return (gotchar);
}

int		ft_check_info(t_args *info, void *mlx)
{
	int s_w;
	int s_h;

	mlx_get_screen_size(mlx, &s_w, &s_h);
	info->width = s_w < info->width ? s_w : info->width;
	info->height = s_h < info->height ? s_h : info->height;
	if (!ft_check_map(info))
		return (ft_error("Error\nMap error borders part"));
	return (1);
}

int		ft_check_cub(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	i--;
	return (!(str[i] == 'b' && str[i - 1] == 'u' && str[i - 2]
		== 'c' && str[i - 3] == '.'));
}
