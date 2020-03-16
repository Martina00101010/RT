/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_etc_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwisozk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 14:10:44 by jwisozk           #+#    #+#             */
/*   Updated: 2019/12/06 14:10:44 by jwisozk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_lst				*ft_new_lst(char *type, void *data)
{
	t_lst			*lst;

	if (!(lst = (t_lst*)ft_malloc(sizeof(t_lst))))
		ft_print(ft_msg(ERROR_29));
	lst->type = type;
	lst->data = data;
	lst->next = NULL;
	return (lst);
}

void				ft_add_lst(t_lst **head, t_lst *new)
{
	if (head != NULL && new != NULL)
	{
		new->next = *head;
		*head = new;
	}
}

int					ft_check_substr(char *str, int num)
{
	if (num == 2)
	{
		if (ft_strequ(str, TYPE) || ft_strequ(str, INTENSITY)
		|| ft_strequ(str, ANGLE) || ft_strequ(str, RADIUS) ||
		ft_strequ(str, SPECULAR))
			return (1);
	}
	if (num == 4)
	{
		if (ft_strequ(str, POSITION) || ft_strequ(str, LOOK_AT)
		|| ft_strequ(str, CENTER) || ft_strequ(str, NORMAL) ||
		ft_strequ(str, TRANSLATION) || ft_strequ(str, TYPE))
			return (1);
	}
	return (0);
}

char				*ft_msg(char *str)
{
    return (ft_strjoin(ERROR, str));
}