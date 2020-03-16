/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_pixels_get.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:32 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/02 01:52:35 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					ft_trace_ray(t_data *data, t_ray ray, int i)
{
	double	lighting;
	t_obj	*o;
	t_pixel	p;
	int		col;

	o = ft_obj_intersect(data->obj_all, &ray, SHADOW_OFF);
	if (o == NULL)
		return (ft_rgb(BACKGROUND));
	ft_pixel_fill(o, &p, &ray);
	if (o->tpt)
		return (ft_transparent_colour(ray, o, data));
	if (o->refl)
		return (refl_colour(ray, p, o, data));
	lighting = ft_lighting(data, &p);
	if (data->f.cartoon)
		return (ft_cartoon(lighting, &p));
	col = ft_multiply_color(lighting, p.color, p.specular);
	return (col);
}

void				ft_pixels_get(t_data *data)
{
	int				i;
	int				j;

	i = 0;
	// i = 230;
	ft_camera_look_at(data);
	while (i < DH)
	{
		j = 0;
		// j = 180;
		while (j < DW)
		{
			ft_camera_ray(data, j, i);
			data->sdl.pixels[i * DW + j] = ft_trace_ray(data, data->ray, START_RECUR);
			j++;
		}
		i++;
	}
}
