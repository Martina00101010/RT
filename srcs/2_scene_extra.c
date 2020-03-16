/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_scene_extra.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:56 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:56 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					*ft_rotation_order(int *arr, int array[3], char *str)
{
	static char		*pattern = "xyz";
	int				i;
	int				j;

	if (ft_strlen(str) != 3)
		ft_print(ft_msg(ERROR_4));
	if (ft_strchr(str, 'x') == NULL || ft_strchr(str, 'y') == NULL ||
	ft_strchr(str, 'z') == NULL)
		ft_print(ft_msg(ERROR_5));
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (str[i] == pattern[j])
				arr[j] = array[i];
			j++;
		}
		i++;
	}
	return (arr);
}

double				*ft_new_arr_d(char *a, char *b, char *c)
{
	double			*arr;

	if (!(arr = (double *)ft_malloc(sizeof(double) * 3)))
		ft_print(ft_msg(ERROR_29));
	arr[0] = ft_atof(a);
	arr[1] = ft_atof(b);
	arr[2] = ft_atof(c);
	return (arr);
}

int					*ft_new_arr_i(char *a, char *b, char *c, char *str)
{
	int				*arr;
	int				array[3];

	array[0] = ft_atoi(a);
	array[1] = ft_atoi(b);
	array[2] = ft_atoi(c);
	if (!(arr = (int *)ft_malloc(sizeof(int) * 3)))
		ft_print(ft_msg(ERROR_29));
	if (str != NULL)
		arr = ft_rotation_order(arr, array, str);
	else
	{
		arr[0] = array[0];
		arr[1] = array[1];
		arr[2] = array[2];
	}
	return (arr);
}
