/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_cartoon.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 00:45:43 by pberge            #+#    #+#             */
/*   Updated: 2020/02/25 00:51:39 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int     ft_cartoon(double lighting, t_pixel *p)
{
    int colour;

   	if (lighting > 0 && lighting < 0.22)
		return (BLACK);
	if (lighting < 0.5)
		lighting = 0.4;
	else if (lighting < 0.9)
		lighting = 0.6;
	else
		lighting = 1.;
    colour = ft_multiply_color(lighting, p->color, p->specular);
    return (colour);
}