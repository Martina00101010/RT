/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_antialiasing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 04:55:59 by pberge            #+#    #+#             */
/*   Updated: 2020/02/29 04:46:17 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int		ft_aggregate_rays(t_data *data, int i, int j)
{
	int	colour;
	int	n;
	int	r;
	int	g;
 	int	b;

	colour = 0;
	n = ALL_RAYS;
	r = 0;
	g = 0;
	b = 0;
	while (--n > -1)
	{
		ft_camera_multiray(data, j, i, n % RAYS_IN_ROW, n / RAYS_IN_ROW);
		colour = ft_trace_ray(data, data->ray, START_RECUR);
		r += ((colour >> 16) & 255);
		g += ((colour >> 8) & 255);
		b += (colour & 255);
	}
	r = r / ALL_RAYS;
	g = g / ALL_RAYS;
	b = b / ALL_RAYS;
	colour = r << 16 | g << 8 | b;
	return (colour);
}

void	ft_antialiasing(t_data *data)
{
	int	colour;
	int	i;
	int	j;

	i = 0;
	ft_camera_look_at(data);
	while (i < DH)
	{
		j = 0;
		while (j < DW)
		{
			colour = ft_aggregate_rays(data, i, j);
			data->sdl.pixels[i * DW + j] = colour;
			j++;
		}
		i++;
	}
}
