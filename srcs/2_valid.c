/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_valid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:11:06 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:11:06 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int 				ft_isvalid(char *str, char *arr[], int max)
{
    int i;

    i = 0;
    while (i < max)
    {
        if (ft_strequ(str, arr[i]) == 1)
            return (i);
        i++;
    }
    return (0);
}

int					ft_isvalid_light(char *str)
{
    static char		*arr[] = LIGHT_TYPES;
    int				max;

    max = sizeof(arr) / sizeof(char*);
    return (ft_isvalid(str, arr, max));
}

int					ft_isvalid_obj(char *str)
{
    static char		*arr[] = OBJ_TYPES;
    int				max;

    max = sizeof(arr) / sizeof(char*);
    return (ft_isvalid(str, arr, max));
}
