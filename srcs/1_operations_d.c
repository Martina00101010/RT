/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_operations_d.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:29 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:29 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

double				ft_lenv(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

double				ft_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double				ft_max(double x, double y)
{
	return (x > y ? x : y);
}

double				ft_min(double x, double y)
{
	return (x < y ? x : y);
}

int					ft_compare_vec3(t_vec3 a, t_vec3 b)
{
	return (a.x == b.x && a.y == b.y && a.z == b.z) ? 1 : 0;
}
