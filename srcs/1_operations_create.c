/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_operations_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:25 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:25 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3				ft_create_vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_ang3				ft_create_ang3(int x, int y, int z)
{
	return ((t_ang3){x, y, z});
}

t_ray				ft_create_ray(t_vec3 origin, t_vec3 direct,
					double t_min, double t_max)
{
	return ((t_ray){origin, direct, t_min, t_max});
}
