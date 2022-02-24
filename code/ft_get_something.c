/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_something.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:00:59 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 00:54:36 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		ft_get_player_dir(char **map, t_raycast *r)
{
	if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'N')
	{
		r->dirx = -1.0;
		r->diry = 0.0;
	}
	else if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'S')
	{
		r->dirx = 1.0;
		r->diry = 0.0;
	}
	else if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'E')
	{
		r->dirx = 0.0;
		r->diry = 1.0;
	}
	else
	{
		r->dirx = 0.0;
		r->diry = -1.0;
	}
}

void		ft_get_plane(char **map, t_raycast *r)
{
	if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'N')
	{
		r->planex = 0.0;
		r->planey = 0.66;
	}
	else if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'S')
	{
		r->planex = 0.0;
		r->planey = -0.66;
	}
	else if (map[(int)(r->posx - 0.5)][(int)(r->posy - 0.5)] == 'E')
	{
		r->planex = 0.66;
		r->planey = 0.0;
	}
	else
	{
		r->planex = -0.66;
		r->planey = 0.0;
	}
}

void		ft_get_player_pos(char **map, t_raycast *r)
{
	int		i;
	int		j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (ft_check_char("NSWE", map[i][j]))
			{
				r->posx = (double)i + 0.5;
				r->posy = (double)j + 0.5;
				break ;
			}
		}
	}
}

void		ft_get_player(t_args *info, t_raycast *r)
{
	ft_get_player_pos(info->map, r);
	ft_get_player_dir(info->map, r);
}

t_raycast	ft_get_ray_params(t_args *info)
{
	t_raycast vars;

	ft_get_player(info, &vars);
	ft_get_plane(info->map, &vars);
	info->map[(int)(vars.posx - 0.5)][(int)(vars.posy - 0.5)] = '0';
	return (vars);
}
