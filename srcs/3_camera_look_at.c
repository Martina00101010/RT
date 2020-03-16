/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_camera_look_at.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:10 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:11:10 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_camera_look_at(t_data *data)
{
    t_vec3 forward;
    t_vec3 left;
    t_vec3 up;
    t_vec3 tmp;

    forward = ft_normalize_vec3(ft_subtract(data->cam->look_at,
                                            data->cam->pos));
    if (forward.x == 0 && forward.z == 0 &&
        (forward.y == 1 || forward.y == -1))
        tmp = ft_create_vec3(0, 0, -1);
    else
        tmp = ft_create_vec3(0, 1, 0);
    left = ft_normalize_vec3(ft_cross_product(tmp, forward));
    up = ft_normalize_vec3(ft_cross_product(forward, left));
    data->cam->forward = forward;
    data->cam->up = up;
    data->cam->left = left;
}