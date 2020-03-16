/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_operations_v.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:32 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:32 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_vec3				ft_cross_product(t_vec3 a, t_vec3 b)
{
	return ((t_vec3){a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x});
}

t_vec3				ft_multiply(double k, t_vec3 v)
{
	return ((t_vec3){v.x * k, v.y * k, v.z * k});
}

t_vec3				ft_add(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3				ft_subtract(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3				ft_normalize_vec3(t_vec3 v)
{
	double			len;
	double			inv_len;

	len = ft_lenv(v);
	if (len > 0)
	{
		inv_len = 1.0 / len;
		v.x *= inv_len;
		v.y *= inv_len;
		v.z *= inv_len;
	}
	return (v);
}
