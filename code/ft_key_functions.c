/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:03:40 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:44:21 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		ft_turn_right(t_raycast *r)
{
	double	olddirx;
	double	oldplanex;

	olddirx = r->dirx;
	oldplanex = r->planex;
	r->dirx = r->dirx * cos(-ROTSPEED) - r->diry * sin(-ROTSPEED);
	r->diry = olddirx * sin(-ROTSPEED) + r->diry * cos(-ROTSPEED);
	r->planex = r->planex * cos(-ROTSPEED) - r->planey * sin(-ROTSPEED);
	r->planey = oldplanex * sin(-ROTSPEED) + r->planey * cos(-ROTSPEED);
}

void		ft_turn_left(t_raycast *r)
{
	double	olddirx;
	double	oldplanex;

	olddirx = r->dirx;
	oldplanex = r->planex;
	r->dirx = r->dirx * cos(ROTSPEED) - r->diry * sin(ROTSPEED);
	r->diry = olddirx * sin(ROTSPEED) + r->diry * cos(ROTSPEED);
	r->planex = r->planex * cos(ROTSPEED) - r->planey * sin(ROTSPEED);
	r->planey = oldplanex * sin(ROTSPEED) + r->planey * cos(ROTSPEED);
}

void		ft_move_up(t_mlx *m, t_raycast *r)
{
	if (m->info.map[(int)(r->posx + r->dirx *
		MOVESPEED)][(int)(r->posy)] == '0')
		r->posx += r->dirx * MOVESPEED;
	if (m->info.map[(int)(r->posx)][(int)(r->posy + r->diry *
		MOVESPEED)] == '0')
		r->posy += r->diry * MOVESPEED;
}

void		ft_move_down(t_mlx *m, t_raycast *r)
{
	if (m->info.map[(int)(r->posx - r->dirx *
		MOVESPEED)][(int)(r->posy)] == '0')
		r->posx -= r->dirx * MOVESPEED;
	if (m->info.map[(int)(r->posx)][(int)(r->posy - r->diry *
		MOVESPEED)] == '0')
		r->posy -= r->diry * MOVESPEED;
}

void		ft_move_left(t_mlx *m, t_raycast *r)
{
	if (m->info.map[(int)(r->posx - r->diry *
		MOVESPEED)][(int)(r->posy)] == '0')
		r->posx -= r->diry * MOVESPEED;
	if (m->info.map[(int)(r->posx)][(int)(r->posy + r->dirx *
		MOVESPEED)] == '0')
		r->posy += r->dirx * MOVESPEED;
}
