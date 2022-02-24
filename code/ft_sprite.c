/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:04:55 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:43:08 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		ft_rev_sp(t_sprite *s, int *j)
{
	float tmp;

	tmp = s->dist[*j - 1];
	s->dist[*j - 1] = s->dist[*j];
	s->dist[*j] = tmp;
	tmp = s->x[*j - 1];
	s->x[*j - 1] = s->x[*j];
	s->x[*j] = tmp;
	tmp = s->y[*j - 1];
	s->y[*j - 1] = s->y[*j];
	s->y[*j] = tmp;
}

void		ft_sort_dist(t_sprite *s)
{
	int i;
	int j;

	i = 1;
	while (i < s->sprite_count)
	{
		j = 1;
		while ((int)s->dist[j] > (int)s->dist[j - 1] && j != 0)
		{
			ft_rev_sp(s, &j);
			--j;
		}
		++i;
	}
}

void		ft_sort_sprite(t_mlx *m, t_sprite *s)
{
	int i;

	i = -1;
	while (++i < s->sprite_count)
	{
		s->dist[i] = ((m->r.posx - s->x[i]) * (m->r.posx - s->x[i])
		+ (m->r.posy - s->y[i]) * (m->r.posy - s->y[i]));
	}
	if (s->sprite_count > 1)
		ft_sort_dist(s);
}

void		ft_set_sprite(t_mlx *m, t_sprite *s, t_print_sprite *sp, int *i)
{
	sp->sp_x = s->x[*i] - m->r.posx;
	sp->sp_y = s->y[*i] - m->r.posy;
	sp->inv_det = 1.0 / (m->r.planex * m->r.diry - m->r.dirx * m->r.planey);
	sp->tform_x = sp->inv_det * (m->r.diry * sp->sp_x - m->r.dirx * sp->sp_y);
	sp->tform_y = sp->inv_det * (-m->r.planey * sp->sp_x + m->r.planex
		* sp->sp_y);
	sp->sp_scr_x = (int)((m->info.width / 2) * (1 + sp->tform_x / sp->tform_y));
	sp->sp_h = abs((int)(m->info.height / (sp->tform_y)));
	sp->draw_start_y = -sp->sp_h / 2 + m->info.height / 2;
	if (sp->draw_start_y < 0)
		sp->draw_start_y = 0;
	sp->draw_end_y = sp->sp_h / 2 + m->info.height / 2;
	if (sp->draw_end_y >= m->info.height)
		sp->draw_end_y = m->info.height - 1;
	sp->sp_w = abs((int)(m->info.height / (sp->tform_y)));
	sp->draw_start_x = -sp->sp_w / 2 + sp->sp_scr_x;
	if (sp->draw_start_x < 0)
		sp->draw_start_x = 0;
	sp->draw_end_x = sp->sp_w / 2 + sp->sp_scr_x;
	if (sp->draw_end_x >= m->info.width)
		sp->draw_end_x = m->info.width - 1;
}

void		ft_print_proper_sprite(t_mlx *m, t_print_sprite *sp,
	int *y, int *st)
{
	*y = sp->draw_start_y;
	while (*y < sp->draw_end_y)
	{
		sp->d = (*y) * 256 - m->info.height * 128 + sp->sp_h * 128;
		sp->tex_y = ((sp->d * TEXHEIGHT) / sp->sp_h) / 256;
		sp->color = get_color(&m->sp, sp->tex_x, sp->tex_y);
		if (sp->color != 0)
			my_mlx_pixel_put(&m->c_f, *st, *y, sp->color);
		(*y)++;
	}
}
