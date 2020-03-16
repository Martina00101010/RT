/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_pixel_fill.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:27 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/02 05:45:51 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	sphere_normal(t_ray *ray, t_obj *obj, t_pixel *p)
{
	(void)ray;
	p->normal = obj->tneg ? ft_subtract(obj->center, p->point) :
		ft_subtract(p->point, obj->center);
	p->normal = ft_normalize_vec3(p->normal);
}

void	cylinder_normal(t_ray *ray, t_obj *obj, t_pixel *p)
{
	t_vec3			oc;
	t_vec3			pc;
	double			m;
	
	oc = ft_subtract(ray->origin, obj->center);
	m = ft_dot(ray->direct, ft_multiply(obj->t, obj->normal)) + ft_dot(oc, obj->normal);
	pc = ft_subtract(p->point, obj->center);
	p->normal = ft_normalize_vec3(ft_subtract(pc, ft_multiply(m, obj->normal)));
}

void	cone_normal(t_ray *ray, t_obj *obj, t_pixel *p)
{
	t_vec3			oc;
	t_vec3			pc;
	double			m;
	
	oc = ft_subtract(ray->origin, obj->center);
	m = ft_dot(ray->direct, ft_multiply(obj->t, obj->normal)) + ft_dot(oc, obj->normal);
	pc = ft_subtract(p->point, obj->center);
	p->normal = ft_normalize_vec3(ft_subtract(pc, ft_multiply(m * (1 + pow(obj->angle, 2)), obj->normal)));
	p->center = obj->center;
}

void			ft_pixel_fill(t_obj *obj, t_pixel *p, t_ray *ray)
{
	p->type = obj->type;
	p->po = ft_multiply(-1, ray->direct);
	p->point = ft_add(ray->origin, ft_multiply(obj->t, ray->direct));
	p->color = obj->color;
	p->specular = obj->specular;
	if (obj->type == PLANE)
		p->normal = obj->normal;
	else if (obj->type == SPHERE)
		sphere_normal(ray, obj, p);
	else if (obj->type == CYLINDER)
		cylinder_normal(ray, obj, p);
	else if (obj->type == CONE)
		cone_normal(ray, obj, p);
	p->normal = (ft_dot(p->normal, p->po) < 0) ?
		ft_multiply(-1, p->normal) : p->normal;
}
