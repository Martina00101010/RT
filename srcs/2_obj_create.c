/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_obj_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:52 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/01 05:07:25 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_obj_create(t_data *data, t_lst *lst)
{
	t_obj			*obj;
	double			*d;
	int				*i;
	int 			type;

	if (!(obj = (t_obj*)ft_malloc(sizeof(t_obj))))
		ft_print(ft_msg(ERROR_29));
	obj->next = data->obj_all != NULL ? data->obj_all : NULL;
	while (lst != NULL)
	{
		i = (int*)lst->data;
		d = (double*)lst->data;
		if (ft_strequ(lst->type, TYPE) && (type = ft_isvalid_obj(lst->data)))
			obj->type = (t_type)type;
		else if (ft_strequ(lst->type, CENTER) == 1)
			obj->center = ft_create_vec3(d[0], d[1], d[2]);
		else if (ft_strequ(lst->type, NORMAL) == 1)
			obj->normal = ft_normalize_vec3(ft_create_vec3(d[0], d[1], d[2]));
		else if (ft_strequ(lst->type, RADIUS))
			obj->radius = ft_atof((char*)lst->data);
		else if (ft_strequ(lst->type, ANGLE))
			obj->angle = TAN(ft_atoi((char*)lst->data));
		else if (ft_strequ(lst->type, COLOR) == 1)
			obj->color = ft_rgb(i[0], i[1], i[2]);
		else if (ft_strequ(lst->type, SPECULAR))
			obj->specular = ft_atoi((char*)lst->data);
		else if (ft_strequ(lst->type, TRANSLATION))
			obj->translation = ft_create_vec3(d[0], d[1], d[2]);
		else if (ft_strequ(lst->type, ROTATION))
			obj->rotation = ft_create_ang3(i[0], i[1], i[2]);
		lst = lst->next;
	}
	obj->center = ft_translate(obj->center, obj->translation);
	obj->normal = ft_rotate(obj->normal,obj->rotation);
	data->obj_all = obj;
}
