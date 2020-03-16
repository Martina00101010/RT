/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_light_create.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:49 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:49 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				ft_light_create(t_data *data, t_lst *lst)
{
	t_light			*l;
	double			*d;
	int 			type;

	if (!(l = (t_light*)ft_malloc(sizeof(t_light))))
		ft_print(ft_msg(ERROR_29));
	l->intensity = -1;
	l->next = data->l != NULL ? data->l : NULL;
	while (lst != NULL)
	{
		if (ft_strequ(lst->type, TYPE) &&  (type = ft_isvalid_light(lst->data)))
			l->type = (t_type_light)type;
		else if (ft_strequ(lst->type, INTENSITY) == 1)
			l->intensity = ft_atof((char*)lst->data);
		else if (ft_strequ(lst->type, POSITION) == 1)
		{
			d = (double*)lst->data;
			l->pos = ft_create_vec3(d[0], d[1], d[2]);
		}
		lst = lst->next;
	}
	data->l = l;
}