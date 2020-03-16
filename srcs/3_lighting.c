/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_lighting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:16 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/02 06:14:11 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				ft_add_diffuse_light(t_pixel *p, t_light *l, t_vec3 *vec_pl)
{
	double			angle_ln;

	angle_ln = ft_dot(p->normal, *vec_pl);
	if (angle_ln > 0)
	{
		return (l->intensity * angle_ln /
		(ft_lenv(p->normal) * ft_lenv(*vec_pl)));
	}
	return (0);
}

double				ft_add_specular_light(t_pixel *p, t_light *l,
					t_vec3 *vec_pl)
{
	t_vec3			vec_pr;
	double			angle_rv;

	if (p->type == CONE)
		p->specular = (ft_compare_vec3(p->center, l->pos) == 1) ? -1 :
		p->specular;
	if (p->specular > 0)
	{
		vec_pr = ft_subtract(ft_multiply(2.0 * ft_dot(p->normal, *vec_pl),
		p->normal), *vec_pl);
		angle_rv = ft_dot(vec_pr, p->po);
		if (angle_rv > 0)
			return (l->intensity * pow(angle_rv /
			(ft_lenv(vec_pr) * ft_lenv(p->po)), p->specular));
	}
	return (0);
}

double		ft_add_shadow(t_data *data, t_light **l,
			t_vec3 *pl, t_pixel *p, t_obj **exc)
{
	t_ray	ray;
	double	t_max;
	t_obj	*tmp;
	int		i;
	double	tptp;
	int		col;

	i = 0;
	tptp = 1;
	tmp = NULL;
	col = ft_rgb(BACKGROUND);
	t_max = (*l)->type == POINT ? 1.0 : INF;
	ray = ft_create_ray(p->point, *pl, E, t_max);
	while ((tmp = ft_obj_intersect(data->obj_all, &ray, SHADOW_ON)) != NULL && i++ < MAX_DEPTH)
	{
		col = ft_rgb_add(
				ft_multiply_color(1. - tptp, col, 0),
				ft_multiply_color(tptp, tmp->color, 0));
		tptp *= (tmp->tpt >= 1.) ? tmp->tptp : 0.;
		if (tmp->tpt < 1)
		{
			(*l) = (*l)->next;
			break ;
		}
		ray.origin = ft_add(ray.origin, ft_multiply(tmp->t, ray.direct));
		ray.t_max = ft_lenv(ft_subtract((*l)->pos, ray.origin));
	}
	if (tptp < 1. && tptp > 0.)
		p->color = ft_rgb_add(
			ft_multiply_color(tptp, p->color, 0),
			ft_multiply_color(1. - tptp, col, 0));
	return (tptp);
}

double	ft_lighting(t_data *data, t_pixel *p)
{
	double			intensity;
	t_vec3			pl;
	t_light 		*l;
	t_obj			*o;
	double			tptp;

	tptp = 1;
	o = NULL;
	l = data->l;
	intensity = 0;
	while (l != NULL)
	{
		if (l->type == AMBIENT)
			intensity += l->intensity;
		else if (l->type == POINT || l->type == DIRECTIONAL)
		{
			pl = (l->type == POINT) ? ft_subtract(l->pos, p->point) : l->pos;
			if ((tptp = ft_add_shadow(data, &l, &pl, p, &o)) == 0)
				continue ;
			intensity += tptp * ft_add_diffuse_light(p, l, &pl);
//			intensity += ft_add_specular_light(p, l, &pl);
		}
		l = l->next;
	}
	return (intensity);
}
