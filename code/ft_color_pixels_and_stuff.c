/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_color_pixels_and_stuff.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:02:14 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:42:44 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->l_l + x * (data->b_p_p / 8));
	*(unsigned int*)dst = color;
}

int		get_color(t_data *data, int x, int y)
{
	unsigned int	color;
	char			*dst;

	dst = data->addr + (y * data->l_l + x * (data->b_p_p / 8));
	color = *(unsigned int*)dst;
	return (color);
}

void	ft_print_texture(t_raycast *vars, t_mlx *m, int x, int y)
{
	vars->tex_y = (int)vars->tex_pos & (TEXHEIGHT - 1);
	vars->tex_pos += vars->step;
	if (!vars->side)
	{
		if (vars->stepx > 0)
			my_mlx_pixel_put(&m->c_f, x, y,
				get_color(&m->so, vars->tex_x, vars->tex_y));
		else
			my_mlx_pixel_put(&m->c_f, x, y,
				get_color(&m->no, vars->tex_x, vars->tex_y));
	}
	else
	{
		if (vars->stepy > 0)
			my_mlx_pixel_put(&m->c_f, x, y,
				get_color(&m->ea, vars->tex_x, vars->tex_y));
		else
			my_mlx_pixel_put(&m->c_f, x, y,
				get_color(&m->we, vars->tex_x, vars->tex_y));
	}
}

void	ft_get_dist_text(t_raycast *vars, t_args *info, t_mlx *m, int *x)
{
	int y;

	if (!vars->side)
		vars->perpwalldist = (vars->mapx - vars->posx + (1 -
			vars->stepx) / 2) / vars->raydirx;
	else
		vars->perpwalldist = (vars->mapy - vars->posy + (1 -
			vars->stepy) / 2) / vars->raydiry;
	ft_get_text(vars, info, &m->sprite, *x);
	y = -1;
	while (++y < info->height)
	{
		if (y < vars->draw_start)
			my_mlx_pixel_put(&m->c_f, *x, y, info->c_color);
		else if (y <= vars->draw_end)
			ft_print_texture(vars, m, *x, y);
		else
			my_mlx_pixel_put(&m->c_f, *x, y, info->f_color);
	}
}

void	ft_empty_keys(t_keys *k)
{
	k->kleft = 0;
	k->kright = 0;
	k->kw = 0;
	k->ks = 0;
	k->kd = 0;
	k->ka = 0;
}
