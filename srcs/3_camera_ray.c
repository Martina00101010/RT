/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_camera_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:13 by jwisozk           #+#    #+#             */
/*   Updated: 2020/02/29 02:00:06 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static double		ft_map_x(int x, double size, int width, double a)
{
	double	xa;

	xa = (double)x + a * RAYS_STEP;
	return (xa * size / (double)width - (size / 2.));
}

static double		ft_map_y(int y, double size, int height, double a)
{
	double	ya;

	ya = (double)y + a * RAYS_STEP;
	return (-ya * size / (double)height + (size / 2.));
}

void				ft_camera_ray(t_data *data, int x, int y)
{
	t_vec3 new_forw;
	t_vec3 new_left;
	t_vec3 new_up;
	t_vec3 left_up;

	new_left = ft_multiply(ft_map_x(x, VW, DW, 0), data->cam->left);
	new_up = ft_multiply(ft_map_y(y, VH, DH, 0), data->cam->up);
	new_forw = ft_multiply(D, data->cam->forward);
	left_up = ft_add(new_up, new_left);
	data->ray = ft_create_ray(data->cam->pos, ft_normalize_vec3(ft_add(left_up, new_forw)), 1, INF);
}

void				ft_camera_multiray(t_data *data, int x, int y, double ax, double ay)
{
	t_vec3 new_forw;
	t_vec3 new_left;
	t_vec3 new_up;
	t_vec3 left_up;

	new_left = ft_multiply(ft_map_x(x, VW, DW, ax), data->cam->left);
	new_up = ft_multiply(ft_map_y(y, VH, DH, ay), data->cam->up);
	new_forw = ft_multiply(D, data->cam->forward);
	left_up = ft_add(new_up, new_left);
	data->ray = ft_create_ray(data->cam->pos, ft_normalize_vec3(ft_add(left_up, new_forw)), 1, INF);
}
