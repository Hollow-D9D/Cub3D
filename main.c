/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:26:17 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:59:39 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "code/cube3d.h"

void		ft_move_right(t_mlx *m, t_raycast *r)
{
	if (m->info.map[(int)(r->posx + r->diry *
		MOVESPEED)][(int)(r->posy)] == '0')
		r->posx += r->diry * MOVESPEED;
	if (m->info.map[(int)(r->posx)][(int)(r->posy - r->dirx *
		MOVESPEED)] == '0')
		r->posy -= r->dirx * MOVESPEED;
}

void		ft_shot_plane(int fd, int all_pix, int zero, int size)
{
	short	plane;

	plane = 1;
	write(fd, &plane, 2);
	plane = 32;
	write(fd, &plane, 2);
	write(fd, &zero, 4);
	write(fd, &size, 4);
	all_pix = 1000;
	write(fd, &all_pix, 4);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

void		ft_screenshot(t_mlx *m)
{
	int		fd;
	int		all_pix;
	int		zero;
	int		pos_pix;
	int		size;

	fd = open("screen.bmp", O_CREAT | O_RDWR, 0666);
	all_pix = m->info.width * m->info.height * 4 + 54;
	zero = 0;
	pos_pix = 54;
	size = m->info.width * m->info.height;
	write(fd, "BM", 2);
	write(fd, &all_pix, 4);
	write(fd, &zero, 4);
	write(fd, &pos_pix, 4);
	pos_pix = 40;
	write(fd, &pos_pix, 4);
	write(fd, &m->info.width, 4);
	write(fd, &m->info.height, 4);
	ft_shot_plane(fd, all_pix, zero, size);
	ft_final_function(fd, m);
}

void		ft_loop(t_args *info, t_mlx *m, int argc)
{
	m->mlx_window = mlx_new_window(m->mlx, info->width, info->height, "cub3d");
	m->r = ft_get_ray_params(info);
	m->sprite.sprite_count = ft_sprite_count(info->map);
	ft_malloc_sprite(&m->sprite, info->width);
	ft_cor_sp_loc(info->map, &m->sprite);
	ft_next_frame(&m->r, info, m);
	if (argc == 3)
		ft_screenshot(m);
	else
	{
		mlx_loop_hook(m->mlx, frame, m);
		mlx_loop(m->mlx);
	}
}

int			main(int argc, char **argv)
{
	int		fd;
	t_mlx	m;
	int		i[2];

	ft_empty_keys(&m.keys);
	m.mlx = mlx_init();
	ft_clear_args(&m.info);
	if (argc != 2)
	{
		if (argc == 3)
		{
			if (ft_strncmp(argv[2], "--save", 10))
				return (ft_error("Error\n2nd argument is not --save"));
		}
		else
			return (ft_error("Error\nWrong argument count"));
	}
	else if (ft_check_cub(argv[1]))
		return (ft_error("Error\n1st argument has wrong extention"));
	fd = open(argv[1], O_RDONLY);
	getinfo(&m.info, fd, m.mlx, i);
	if (!ft_ini_tex(&m.info, &m))
		return (ft_error("Error\ntexture error"));
	ft_loop(&m.info, &m, argc);
}
