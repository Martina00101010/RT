/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 15:19:43 by jwisozk           #+#    #+#             */
/*   Updated: 2020/03/03 05:50:56 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <time.h>

void	ft_free(t_data *data)
{
	t_obj	*o;

	o = data->obj_all;
	while (o != NULL)
	{
		if (o->radius < 0.9 && o->radius > 0.6)
			free(o->neg);
		o = o->next;
	}
}

t_obj	*ft_neg_obj(void)
{
	t_obj	*obj;

	obj = (t_obj *)malloc(sizeof(t_obj));
	ft_bzero(obj, sizeof(t_obj));
	obj->type = SPHERE;
	obj->center = (t_vec3){ -0.5, -0.4, -2.4 };
	obj->radius = 0.5;
	obj->tneg = 1;
	obj->hollow = 1;
	obj->color = 0xFF0000;
	obj->neg = NULL;
	return (obj);
}

void	ft_add_neg(t_data *data)
{
	t_obj	*tmp;

	tmp = data->obj_all;
	while (tmp != NULL)
	{	
		if (tmp->type == SPHERE && tmp->color == 0xff0000)
		{
			tmp->tpt = 1.001;
			tmp->tptp = 0.95;
		}
		if (tmp->type == SPHERE && tmp->color == 0xff)
		{
			tmp->sliced = 1;
			tmp->normal = ft_normalize_vec3((t_vec3){ 0., 0.5, 1. });
			tmp->slice_up = ft_multiply(1, tmp->normal);
			tmp->slice_down = ft_multiply(1, tmp->normal);
			tmp->len_up = 1.;
			tmp->len_down = 0.6;
			tmp->tpt = 1.;
			tmp->tptp = 0.21;
		}
		if (tmp->type == CONE && tmp->color == 0x800080)
		{
			tmp->sliced = 1;
			tmp->slice_up = ft_multiply(1.0, tmp->normal);
			tmp->slice_down = ft_multiply(-1.0, tmp->normal);
			tmp->len_down = 0.0;
			tmp->len_up = 1.6;
			// tmp->tpt = 1.;
			// tmp->tptp = 0.79;
		}
		if (tmp->type == CONE && tmp->color == 0xFFFF00)
		{
			tmp->sliced = 1;
			tmp->slice_up = ft_multiply(1.0, tmp->normal);
			tmp->slice_down = ft_multiply(-1.0, tmp->normal);
			tmp->len_down = 1.6;
			tmp->len_up = 1.6;
			// tmp->tpt = 1.;
			// tmp->tptp = 0.79;
		}
		if (tmp->type == CYLINDER)
		{
			tmp->sliced = 1;
			tmp->slice_up = tmp->normal;
			tmp->slice_down = ft_multiply(-1, tmp->slice_up);
			tmp->len_up = 0;//ft_lenv(tmp->slice_up);
			tmp->len_down = 0.5;
			tmp->tpt = 1.;
			tmp->tptp = 0.7;
		}
// 		if (tmp->type == PLANE)
// 		{
// 			tmp->tpt = 1.;
// 			tmp->tptp = 0.79;
// 		}
// 		if (tmp->radius < 0.9 && tmp->radius > 0.6)
// 		{
// 			tmp->tpt = 1.7;
// 			tmp->tptp = 0.42;
// //			tmp->neg = ft_neg_obj();
// 			return ;
// 		}
		tmp = tmp->next;
	}
}

void	ft_add_refl(t_data *data)
{
	t_obj	*tmp;

	tmp = data->obj_all;
	while (tmp != NULL)
	{
		// if (tmp->radius < 0.9 && tmp->radius > 0.6)
		if (tmp->type == SPHERE)
			tmp->refl = 1;
		tmp = tmp->next;
	}
}

int					main(int argc, char **argv)
{
	int				fd;
	t_data			data;
	// t_render		r[RENDERS_NUM];


	if (argc == 2)
	{
	    /* STEP 1 */
		clock_t time = clock();;
		ft_check_argv(argv[1]);
		ft_open_file(argv[1], &fd);
        ft_bzero(&data, sizeof(t_data));

        /* STEP 2 */
		ft_get_scene(fd, &data); // Переписать чтение сцены
		ft_add_neg(&data);
//		ft_add_refl(&data);
		ft_close_file(fd);

		/* STEP 3 */
		// data.r[0] = ft_pixels_get;
		// data.r[1] = ft_antialiasing;
		// data.r[0](&data);
		ft_pixels_get(&data);
		// ft_antialiasing(&data);
		ft_free(&data);
		ft_clean();
		printf("%f\n", (double)(clock() - time)/CLOCKS_PER_SEC);

        /* STEP 4 */
		ft_sdl2_main(&data.sdl);
	}
	else
		ft_print(USAGE);
	return (0);
}
