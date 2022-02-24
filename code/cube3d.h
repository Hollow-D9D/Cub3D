/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 13:28:16 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 02:00:24 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# define TEXWIDTH 64
# define TEXHEIGHT 64
# define ROTSPEED 0.115
# define MOVESPEED 0.2

# include <math.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../libs/mlx/mlx.h"
# include "../libs/libft/libft.h"

typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			b_p_p;
	int			l_l;
	int			endian;
}				t_data;

typedef struct	s_raycast
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	int		mapx;
	int		mapy;
	double	sdistx;
	double	sdisty;
	double	ddistx;
	double	ddisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		side;
	int		hit;
	int		line_height;
	int		draw_start;
	int		draw_end;
	double	wallx;
	int		tex_num;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
}				t_raycast;

typedef struct	s_args
{
	int		height;
	int		width;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sp;
	int		f_color;
	int		c_color;
	char	**map;
}				t_args;

typedef struct	s_print_sprite
{
	double		sp_x;
	double		sp_y;
	double		inv_det;
	double		tform_x;
	double		tform_y;
	int			sp_scr_x;
	int			sp_h;
	int			draw_start_y;
	int			draw_end_y;
	int			sp_w;
	int			draw_start_x;
	int			draw_end_x;
	int			tex_x;
	int			d;
	int			tex_y;
	int			color;
}				t_print_sprite;

typedef struct	s_keys
{
	int	kw;
	int	ks;
	int	ka;
	int	kd;
	int	kleft;
	int	kright;
	int	kup;
	int	kdown;
	int exit;
}				t_keys;

typedef struct	s_sprite
{
	int		sprite_count;
	float	*x;
	float	*y;
	float	*dist;
	double	*c_s;
}				t_sprite;

typedef struct	s_mlx
{
	void		*mlx;
	void		*mlx_window;
	char		c;
	t_data		so;
	t_data		no;
	t_data		ea;
	t_data		we;
	t_data		sp;
	t_data		c_f;
	t_raycast	r;
	t_args		info;
	t_keys		keys;
	t_sprite	sprite;
}				t_mlx;

int				ft_error(char *str);
int				ft_isspace(char c);
int				ft_trgb(int t, int r, int g, int b);
int				ft_ini_map(const char *line, t_args *info, int x);
int				ft_parse_map(char *line, t_args *info, int x);
int				ft_check_element(char **info, int i, int j, char c);
void			ft_check_borders(char **info, int *gotchar);
int				ft_check_map(t_args *info);
int				ft_check_info(t_args *info, void *mlx);
int				ft_take_num(const char *line, int *i);
int				give_r(t_args *info, const char *line, int i);
int				give_color(t_args *info, const char *line, int i, char c);
int				give_ea(t_args *info, const char *line, int i);
int				give_we(t_args *info, const char *line, int i);
int				give_s(t_args *info, const char *line, int i);
int				give_no(t_args *info, const char *line, int i);
int				give_so(t_args *info, const char *line, int i);
int				ft_ini_tex(t_args *args, t_mlx *mlx);
void			ft_clear_args(t_args *args);
int				getinfo(t_args *info, int fd, void *mlx, int *i);
int				ft_close_win(t_mlx *m);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			ft_get_player_dir(char **map, t_raycast *r);
void			ft_get_plane(char **map, t_raycast *r);
void			ft_get_player_pos(char **map, t_raycast *r);
void			ft_get_player(t_args *info, t_raycast *r);
t_raycast		ft_get_ray_params(t_args *info);
void			ft_ini_dist(t_raycast *vars);
void			ft_ini_ray_params(int x, t_args *info, t_raycast *vars);
void			ft_check_next_square(t_args *info, t_raycast *vars);
void			ft_get_text(t_raycast *vars, t_args *info, t_sprite *s, int x);
int				get_color(t_data *data, int x, int y);
void			ft_print_texture(t_raycast *vars, t_mlx *m, int x, int y);
void			ft_get_dist_text(t_raycast *vars, t_args *info, t_mlx *m,
				int *x);
void			ft_turn_right(t_raycast *r);
void			ft_turn_left(t_raycast *r);
void			ft_move_up(t_mlx *m, t_raycast *r);
void			ft_move_down(t_mlx *m, t_raycast *r);
void			ft_move_right(t_mlx *m, t_raycast *r);
void			ft_move_left(t_mlx *m, t_raycast *r);
void			ft_rev_sp(t_sprite *s, int *j);
void			ft_sort_dist(t_sprite *s);
void			ft_sort_sprite(t_mlx *m, t_sprite *s);
void			ft_set_sprite(t_mlx *m, t_sprite *s, t_print_sprite *sp,
				int *i);
void			ft_print_proper_sprite(t_mlx *m, t_print_sprite *sp, int *y,
				int *st);
char			*ft_app_line(int *x, char *buff, char *tmp);
void			ft_print_sprite(t_mlx *m, t_sprite *s);
void			ft_next_frame(t_raycast *vars, t_args *info, t_mlx *m);
int				key_hook(t_mlx *m);
int				ft_key_press(int keycode, t_keys *k);
int				ft_key_release(int keycode, t_keys *k);
int				frame(t_mlx *m);
int				ft_sprite_count(char **map);
void			ft_malloc_sprite(t_sprite *s, int width);
void			ft_cor_sp_loc(char **map, t_sprite *s);
void			ft_shot_plane(int fd, int all_pix, int zero, int size);
void			ft_screenshot(t_mlx *m);
void			ft_loop(t_args *info, t_mlx *m, int argc);
void			ft_empty_keys(t_keys *k);
int				ft_check_cub(char *str);
void			ft_final_function(int fd, t_mlx *m);

#endif
