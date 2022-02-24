/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:49:23 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 01:26:09 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int		ft_close_win(t_mlx *m)
{
	mlx_destroy_window(m->mlx, m->mlx_window);
	exit(0);
	return (0);
}

int		ft_error(char *str)
{
	perror(str);
	exit(1);
	return (1);
}

char	*ft_app_line(int *x, char *buff, char *tmp)
{
	(*x)++;
	buff = ft_strjoin(buff, "\n");
	buff = ft_strjoin(buff, tmp);
	free(tmp);
	return (buff);
}
