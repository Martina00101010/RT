/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_refract.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 18:05:58 by pberge            #+#    #+#             */
/*   Updated: 2020/02/23 02:12:26 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	print_v(t_vec3 v)
{
	printf("%f %f %f    ", v.x, v.y, v.z);
}

t_ray	ft_reflect(t_ray ray, double t, t_vec3 norm)
{
	t_ray	rfl;

	rfl.origin = ft_add(ray.origin, ft_multiply(t, ray.direct));
	rfl.direct = ft_subtract(ray.direct, ft_multiply(2 * ft_dot(norm, ray.direct), norm));
	rfl.direct = ft_normalize_vec3(rfl.direct);
	rfl.t_min = E;
	rfl.t_max = ray.t_max;
	return (rfl);
}

t_ray	ft_refract(t_ray ray, double t, t_vec3 norm, double tpt)
{
	double	nu;
	t_ray	rfr;
	double	c0;
	double	c1;

	nu = 1. / tpt;
	c0 = ft_dot(ray.direct, norm);
	if (c0 < 0)
		c0 = c0 * -1.;
	else
	{
		norm = ft_multiply(-1, norm);
		nu = tpt / 1.;
	}
	c1 = 1. - nu * nu * (1. - c0 * c0);
	if (c1 < 0)
		c1 = 0;
	c1 = sqrt(c1);
/* create ray */
	rfr.origin = ft_add(ray.origin, ft_multiply(t, ray.direct));
	rfr.t_min = E;
	rfr.t_max = INF;
/* calculate refracted */
	rfr.direct = ft_add(ft_multiply(nu, ray.direct),
		ft_multiply(nu * c0 - c1, norm));
	rfr.direct = ft_normalize_vec3(rfr.direct);
	return (rfr);
}
