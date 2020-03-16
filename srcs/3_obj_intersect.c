/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_obj_intersect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:20 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/03 05:42:34 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_compare_t(double t1, double t2, double p[2])
{
	if (t1 == t2)
		return ;
	else if (t1 > E && t2 > E)
	{
		p[0] = ft_min(t1, t2);
		p[1] = t1 < t2 ? t2 : t1;
	}
	else if (E < t1 && t1 < INF)
	{
		p[0] = t1;
		p[1] = INF;
	}
	else if (E < t2 && t2 < INF)
	{
		p[0] = t2;
		p[1] = INF;
	}
	else
	{
		p[0] = INF;
		p[1] = INF;
	}
}

double			ft_pl_calc(t_ray *ray, t_obj *obj, t_obj **ret)
{
	double			angle;
	double			t;
	t_vec3			op;

	t = INF;
	*ret = obj;
	angle = ft_dot(obj->normal, ray->direct);
	if (angle != 0)
	{
		op = ft_subtract(obj->center, ray->origin);
		t = ft_dot(op, obj->normal) / angle;
	}
	return (t);
}

void	sphere(double k[3], t_vec3 oc, t_ray *ray, t_obj *obj)
{
	k[0] = ft_dot(ray->direct, ray->direct);
	k[1] = 2. * ft_dot(oc, ray->direct);
	k[2] = ft_dot(oc, oc) - obj->radius * obj->radius;
}

void	cylinder(double k[3], t_vec3 oc, t_ray *ray, t_obj *obj)
{
	double	tmp;

	tmp = ft_dot(ray->direct, obj->normal);
	k[0] = ft_dot(ray->direct, ray->direct);
	k[0] -= tmp * tmp;
	k[1] = ft_dot(ray->direct, obj->normal) * ft_dot(oc, obj->normal);
	k[1] = 2. * (ft_dot(ray->direct, oc) - k[1]);
	tmp = ft_dot(oc, obj->normal);
	k[2] = ft_dot(oc, oc);
	k[2] -= obj->radius * obj->radius + tmp * tmp;
}

void	cone(double k[3], t_vec3 oc, t_ray *ray, t_obj *obj)
{
	double	tmp;

	tmp = 1. + obj->angle * obj->angle;
	k[0] = ft_dot(ray->direct, ray->direct);
	k[0] -= tmp * pow(ft_dot(ray->direct, obj->normal), 2);
	k[1] = tmp * ft_dot(ray->direct, obj->normal);
	k[1] *= ft_dot(oc, obj->normal);
	k[1] = 2. * (ft_dot(ray->direct, oc) - k[1]);
	k[2] = ft_dot(oc, oc);
	k[2] -= tmp * pow(ft_dot(oc, obj->normal), 2);
}

void	solve_disc(double k[3], double p[2])
{
	double			discriminant;
	double			t1;
	double			t2;

	discriminant = k[1] * k[1] - 4. * k[0] * k[2];
	p[0] = INF;
	p[1] = INF;
	if (discriminant >= 0)
	{
		p[0] = (-k[1] + sqrt(discriminant)) / (2. * k[0]);
		p[1] = (-k[1] - sqrt(discriminant)) / (2. * k[0]);
	}
}

void	ft_calc_coeffs(t_ray *ray, t_obj *obj, double p[2])
{
	t_vec3			oc;
	double			k[3];

	oc = ft_subtract(ray->origin, obj->center);
	if (obj->type == SPHERE)
		sphere(k, oc, ray, obj);
	else if (obj->type == CYLINDER)
		cylinder(k ,oc, ray, obj);
	else if (obj->type == CONE)
		cone(k, oc, ray, obj);
	solve_disc(k, p);
	ft_compare_t(p[0], p[1], p);
	if (obj->sliced)
		slice(ray, obj, p);
}

void	ft_shadow_ray(t_ray *ray, t_obj *obj, double p[2], t_obj **ret)
{
	double	n[2];
	double	tmp;

	ft_calc_coeffs(ray, obj->neg, n);
	if (obj->neg->hollow == 1 && n[1] < 0 && n[0] > 0)
	{
		tmp = n[1];
		n[1] = n[0];
		n[0] = tmp;
	}
	if (obj->neg->hollow == 1 && p[1] < n[0] && n[0] < p[0] && p[0] < n[1])
	{
		p[0] = INF;//p[1];
	}
	if (obj->neg->hollow == 0 && p[1] < n[1] && n[1] < p[0] && p[0] < n[0])
	{
		p[0] = INF;//n[0];
		//p[1] = INF;//n[1];
	}
//	*ret = NULL;//obj->neg;
}

void	ft_calc_neg(t_ray *ray, t_obj *obj, double p[2], t_obj **ret)
{
	double	n[2];

	ft_calc_coeffs(ray, obj->neg, n);
	if (p[0] < n[1] && n[1] < p[1] && n[0] < p[0])
	{
		if (obj->neg->hollow == 1)
			p[0] = p[1];
		else
		{
			*ret = obj->neg;
			p[0] = n[1];
			p[1] = n[0];
		}
	}
}

double	ft_obj_calc(t_ray *ray, t_obj *obj, t_obj **ret, int shadow)
{
	double			p[2];

	*ret = obj;
	p[0] = INF;
	p[1] = INF;
	ft_calc_coeffs(ray, obj, p);
	if (p[0] != INF && obj->neg != NULL)
	{
		if (shadow)
			ft_shadow_ray(ray, obj, p, ret);
		else
			ft_calc_neg(ray, obj, p, ret);
	}
	if (shadow && obj->tpt > 1.)
		return (p[1]);
	return (p[0]);
}

t_obj			*ft_obj_intersect(t_obj *obj, t_ray *ray, int shadow)
{
	t_obj 		*obj_clos;
	t_obj		*ret;
	double		t;
	double		t_min;

	obj_clos = NULL;
	ret = NULL;
	t_min = INF;
	while (obj != NULL)
	{
		t = (obj->type == PLANE) ?
			ft_pl_calc(ray, obj, &ret) : ft_obj_calc(ray, obj, &ret, shadow);
		if (t < t_min && ray->t_min < t && t < ray->t_max)
		{
			obj_clos = ret;
			t_min = t;
			obj_clos->t = t_min;
		}
		obj = obj->next;
	}
	return (obj_clos);
}
