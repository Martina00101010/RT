/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_slice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 01:40:27 by pberge            #+#    #+#             */
/*   Updated: 2020/03/03 02:55:15 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int    slice_part(t_ray *ray, t_obj *obj, double p)
{
    t_vec3  point;
    double  head;
    double  tail;

    point = ft_add(ray->origin, ft_multiply(p, ray->direct));
    point = ft_subtract(point, obj->center);
    if (ft_dot(obj->normal, point) > 0.)
    {
        head = ft_dot(obj->slice_up, point);
        tail = ft_dot(obj->slice_down, point);
        if (head > 0. && head < obj->len_up &&
            (tail <= 0. || tail >= obj->len_down))
            return (0);
    }
    else
    {
        head = ft_dot(obj->slice_down, point);
        tail = ft_dot(obj->slice_up, point);
        if (head > 0. && head < obj->len_down &&
            (tail <= 0. || tail >= obj->len_up))
            return (0);
    }
    return (1);
}

void    slice(t_ray *ray, t_obj *obj, double p[2])
{
    double  tmp;
    int     i;

    i = 0;
    if (p[0] == p[1] && p[0] == INF)
        return ;
    while (i < 2 && slice_part(ray, obj, p[i]))
        i++;
    if (i == 2)
    {
        p[0] = INF;
        p[1] = INF;
    }
    else if (i == 1)
    {
        tmp = p[0];
        p[0] = p[1];
        p[1] = tmp;
    }
}