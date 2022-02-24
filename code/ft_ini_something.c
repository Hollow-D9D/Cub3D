/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ini_something.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:01:31 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:47:20 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		ft_ini_tex(t_args *args, t_mlx *mlx)
{
	int w;
	int h;

	if (!(mlx->so.img = mlx_xpm_file_to_image(mlx->mlx, args->so, &w, &h)))
		return (0);
	mlx->so.addr = mlx_get_data_addr(mlx->so.img, &mlx->so.b_p_p, &mlx->so.l_l,
		&mlx->so.endian);
	if (!(mlx->no.img = mlx_xpm_file_to_image(mlx->mlx, args->no, &w, &h)))
		return (0);
	mlx->no.addr = mlx_get_data_addr(mlx->no.img, &mlx->no.b_p_p, &mlx->no.l_l,
		&mlx->no.endian);
	if (!(mlx->ea.img = mlx_xpm_file_to_image(mlx->mlx, args->ea, &w, &h)))
		return (0);
	mlx->ea.addr = mlx_get_data_addr(mlx->ea.img, &mlx->ea.b_p_p, &mlx->ea.l_l,
		&mlx->ea.endian);
	if (!(mlx->we.img = mlx_xpm_file_to_image(mlx->mlx, args->we, &w, &h)))
		return (0);
	mlx->we.addr = mlx_get_data_addr(mlx->we.img, &mlx->we.b_p_p, &mlx->we.l_l,
		&mlx->we.endian);
	if (!(mlx->sp.img = mlx_xpm_file_to_image(mlx->mlx, args->sp, &w, &h)))
		return (0);
	mlx->sp.addr = mlx_get_data_addr(mlx->sp.img, &mlx->sp.b_p_p, &mlx->sp.l_l,
		&mlx->sp.endian);
	return (1);
}

void	ft_ini_dist(t_raycast *vars)
{
	if (vars->raydirx < 0)
	{
		vars->stepx = -1;
		vars->sdistx = (vars->posx - vars->mapx) * vars->ddistx;
	}
	else
	{
		vars->stepx = 1;
		vars->sdistx = (vars->mapx + 1.0 - vars->posx) * vars->ddistx;
	}
	if (vars->raydiry < 0)
	{
		vars->stepy = -1;
		vars->sdisty = (vars->posy - vars->mapy) * vars->ddisty;
	}
	else
	{
		vars->stepy = 1;
		vars->sdisty = (vars->mapy + 1.0 - vars->posy) * vars->ddisty;
	}
}

void	ft_ini_ray_params(int x, t_args *info, t_raycast *vars)
{
	vars->camerax = 2 * x / (double)info->width - 1;
	vars->raydirx = vars->dirx + vars->planex * vars->camerax;
	vars->raydiry = vars->diry + vars->planey * vars->camerax;
	vars->mapx = (int)vars->posx;
	vars->mapy = (int)vars->posy;
	vars->ddistx = fabs(1 / vars->raydirx);
	vars->ddisty = fabs(1 / vars->raydiry);
	vars->hit = 0;
	ft_ini_dist(vars);
}

void	ft_check_next_square(t_args *info, t_raycast *vars)
{
	if (vars->sdistx < vars->sdisty)
	{
		vars->sdistx += vars->ddistx;
		vars->mapx += vars->stepx;
		vars->side = 0;
	}
	else
	{
		vars->sdisty += vars->ddisty;
		vars->mapy += vars->stepy;
		vars->side = 1;
	}
	if (info->map[vars->mapx][vars->mapy] == '1')
		vars->hit = 1;
}

void	ft_get_text(t_raycast *vars, t_args *info, t_sprite *s, int x)
{
	s->c_s[x] = vars->perpwalldist;
	vars->line_height = (int)(info->height / vars->perpwalldist);
	vars->draw_start = -vars->line_height / 2 + info->height / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + info->height / 2;
	if (vars->draw_end >= info->height)
		vars->draw_end = info->height - 1;
	vars->tex_num = info->map[vars->mapx][vars->mapy] - 1;
	if (!vars->side)
		vars->wallx = vars->posy + vars->perpwalldist *
	vars->raydiry;
	else
		vars->wallx = vars->posx + vars->perpwalldist *
	vars->raydirx;
	vars->wallx -= floor(vars->wallx);
	vars->tex_x = (int)(vars->wallx * (double)(TEXWIDTH));
	if (!vars->side && vars->raydirx > 0)
		vars->tex_x = TEXWIDTH - vars->tex_x - 1;
	if (vars->side == 1 && vars->raydiry < 0)
		vars->tex_x = TEXWIDTH - vars->tex_x - 1;
	vars->step = 1.0 * TEXHEIGHT / vars->line_height;
	vars->tex_pos = (vars->draw_start - info->height / 2 +
		vars->line_height / 2) * vars->step;
}
