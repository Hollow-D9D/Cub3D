/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_text_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharutyu <tharutyu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/26 23:57:46 by tharutyu          #+#    #+#             */
/*   Updated: 2021/04/27 00:59:20 by tharutyu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

int	give_ea(t_args *info, const char *line, int i)
{
	int len;

	i += 2;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (!ft_isspace(line[i + len]))
		len++;
	info->ea = ft_substr(line, i, len);
	i += ft_strlen(info->ea);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	give_we(t_args *info, const char *line, int i)
{
	int len;

	i += 2;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (!ft_isspace(line[i + len]))
		len++;
	info->we = ft_substr(line, i, len);
	i += ft_strlen(info->we);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	give_s(t_args *info, const char *line, int i)
{
	int len;

	i++;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (!ft_isspace(line[i + len]))
		len++;
	info->sp = ft_substr(line, i, len);
	i += ft_strlen(info->sp);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	give_no(t_args *info, const char *line, int i)
{
	int len;

	i += 2;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (!ft_isspace(line[i + len]))
		len++;
	info->no = ft_substr(line, i, len);
	i += ft_strlen(info->no);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

int	give_so(t_args *info, const char *line, int i)
{
	int len;

	i += 2;
	len = 0;
	while (ft_isspace(line[i]))
		i++;
	while (!ft_isspace(line[i + len]))
		len++;
	info->so = ft_substr(line, i, len);
	i += ft_strlen(info->so);
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}
