/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_camera_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:41 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:41 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void					ft_camera_create(t_data *data, t_lst *lst)
{
	t_cam 	*cam;
	double	*d;

	if (!(cam = (t_cam*)ft_malloc(sizeof(t_cam))))
		ft_print(ft_msg(ERROR_29));
	while (lst != NULL)
	{
		d = (double*)lst->data;
		if (ft_strequ(lst->type, POSITION) == 1)
			cam->pos = ft_create_vec3(d[0], d[1], d[2]);
		else if (ft_strequ(lst->type, LOOK_AT) == 1)
			cam->look_at = ft_create_vec3(d[0], d[1], d[2]);
		lst = lst->next;
	}
	data->cam = cam;
}