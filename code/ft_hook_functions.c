/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hook_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:04:08 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 00:53:37 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void		ft_next_frame(t_raycast *vars, t_args *info, t_mlx *m)
{
	int			x;

	m->c_f.img = mlx_new_image(m->mlx, info->width, info->height);
	m->c_f.addr = mlx_get_data_addr(m->c_f.img, &m->c_f.b_p_p, &m->c_f.l_l,
		&m->c_f.endian);
	x = -1;
	while (++x < info->width)
	{
		ft_ini_ray_params(x, info, vars);
		while (vars->hit == 0)
			ft_check_next_square(info, vars);
		ft_get_dist_text(vars, info, m, &x);
	}
	ft_sort_sprite(m, &m->sprite);
	ft_print_sprite(m, &m->sprite);
	mlx_put_image_to_window(m->mlx, m->mlx_window, m->c_f.img, 0, 0);
}

int			key_hook(t_mlx *m)
{
	if (m->keys.kleft)
		ft_turn_left(&m->r);
	if (m->keys.kright)
		ft_turn_right(&m->r);
	if (m->keys.kw)
		ft_move_up(m, &m->r);
	if (m->keys.ks)
		ft_move_down(m, &m->r);
	if (m->keys.ka)
		ft_move_left(m, &m->r);
	if (m->keys.kd)
		ft_move_right(m, &m->r);
	if (m->keys.exit == 1)
		ft_close_win(m);
	ft_next_frame(&m->r, &m->info, m);
	return (0);
}

int			ft_key_press(int keycode, t_keys *k)
{
	if (keycode == 123)
		k->kleft = 1;
	if (keycode == 124)
		k->kright = 1;
	if (keycode == 13)
		k->kw = 1;
	if (keycode == 1)
		k->ks = 1;
	if (keycode == 0)
		k->ka = 1;
	if (keycode == 2)
		k->kd = 1;
	if (keycode == 53)
		k->exit = 1;
	return (0);
}

int			ft_key_release(int keycode, t_keys *k)
{
	if (keycode == 123)
		k->kleft = 0;
	if (keycode == 124)
		k->kright = 0;
	if (keycode == 13)
		k->kw = 0;
	if (keycode == 1)
		k->ks = 0;
	if (keycode == 0)
		k->ka = 0;
	if (keycode == 2)
		k->kd = 0;
	return (0);
}

int			frame(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->c_f.img);
	mlx_hook(m->mlx_window, 2, 1L << 0, ft_key_press, &m->keys);
	mlx_hook(m->mlx_window, 3, 1L << 1, ft_key_release, &m->keys);
	key_hook(m);
	ft_next_frame(&m->r, &m->info, m);
	return (0);
}
