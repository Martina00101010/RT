/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_refl_colour.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 01:23:25 by pberge            #+#    #+#             */
/*   Updated: 2020/02/23 03:30:57 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		refl_colour(t_ray ray, t_pixel p, t_obj *o, t_data *data)
{
	int		r;
	int		i;
	t_ray	lect;
	double	l;
	double	lectp;

	i = 0;
	l = ft_lighting(data, &p);
	r = ft_multiply_color(l, o->color, 0);
	while (o->refl > 0 && i++ < MAX_DEPTH)
	{
		lectp = o->refl;
		lect = ft_reflect(ray, o->t, p.normal);
		o = ft_obj_intersect(data->obj_all, &lect, SHADOW_OFF);
		if (o == NULL)
			return (r = ft_rgb_add(
			ft_multiply_color((1.-lectp), r, 0),
			ft_multiply_color(lectp * l, ft_rgb(BACKGROUND), 0)));
		ft_pixel_fill(o, &p, &lect);
		l = ft_lighting(data, &p);
		r = ft_rgb_add(
			ft_multiply_color((1.-lectp), r, 0),
			ft_multiply_color(lectp * l, o->color, o->specular));
		ray = lect;
	}
	return (r);
}
