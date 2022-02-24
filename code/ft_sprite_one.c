/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprite_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/27 00:05:36 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:44:34 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	ft_print_sprite(t_mlx *m, t_sprite *s)
{
	t_print_sprite	sp;
	int				i;
	int				j;
	int				st;

	i = -1;
	while (++i < s->sprite_count)
	{
		ft_set_sprite(m, s, &sp, &i);
		st = sp.draw_start_x;
		while (st < sp.draw_end_x)
		{
			sp.tex_x = (int)(256 * (st - (-sp.sp_w / 2 + sp.sp_scr_x)) *
				TEXWIDTH / sp.sp_w) / 256;
			if (sp.tform_y > 0 && st > 0 && st < m->info.width && sp.tform_y
				< s->c_s[st])
			{
				ft_print_proper_sprite(m, &sp, &j, &st);
			}
			++st;
		}
	}
}

void	ft_final_function(int fd, t_mlx *m)
{
	int i;
	int j;
	int color;

	i = m->info.height;
	while (--i >= 0)
	{
		j = -1;
		while (++j < m->info.width)
		{
			color = get_color(&m->c_f, j, i);
			write(fd, &color, 4);
		}
	}
	exit(0);
}

int		ft_sprite_count(char **map)
{
	int i;
	int j;
	int count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '2')
				count++;
		}
	}
	return (count);
}

void	ft_malloc_sprite(t_sprite *s, int width)
{
	if (!(s->x = malloc(sizeof(float) * s->sprite_count)))
		printf("Error\nNo memory allocated");
	if (!(s->y = malloc(sizeof(float) * s->sprite_count)))
		printf("Error\nNo memory allocated");
	if (!(s->dist = malloc(sizeof(float) * s->sprite_count)))
		printf("Error\nNo memory allocated");
	if (!(s->c_s = malloc(sizeof(double) * width)))
		printf("Error\nNo memory allocated");
}

void	ft_cor_sp_loc(char **map, t_sprite *s)
{
	int i;
	int j;
	int count;

	i = -1;
	count = 0;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == '2')
			{
				s->x[count] = i + 0.5;
				s->y[count] = j + 0.5;
				count++;
			}
		}
	}
}
