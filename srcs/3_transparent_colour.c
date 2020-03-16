/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_transparent_colour.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:18:34 by pberge            #+#    #+#             */
/*   Updated: 2020/02/29 06:13:19 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_tree  *ft_tree_new(t_dot dot)
{
    t_tree  *new;

    new = NULL;
    if((new = (t_tree *)malloc(sizeof(t_tree))) != NULL)
    {
        ft_bzero(new, sizeof(t_tree));
        new->dot = dot;
        new->left = NULL;
        new->right = NULL;
        new->parent = NULL;
    }
    return (new);
}

void    ft_free_tree(t_tree **root)
{
    t_tree  *node;

    node = *root;
    while (node->parent != NULL)
        node = node->parent;
    while (node->left != NULL)
        node = node->left;
    while (node != NULL)
    {
        if (node->right != NULL)
        {
            node = node->right;
            while (node->left != NULL)
                node = node->left;
        }
        else
        {
            while (node->parent != NULL && node->parent->right == node)
            {
                node = node->parent;
                free(node->right);
                node->right = NULL;
            }
            if (node->parent == NULL)
                break ;
            node = node->parent;
            free(node->left);
            node->left = NULL;
        }
    }
    free(node);
    *root = NULL;
}

double   koef_refr(double nt, t_vec3 norm, t_ray rfr, t_ray ray)
{
	double	ni;
	double	paral;
	double	perpe;
	double	cosi;
	double	cost;

	ni = 1.;
	cosi = ft_dot(ray.direct, norm);
	cost = ft_dot(rfr.direct, norm);
	paral = (nt * cosi - ni * cost) / (nt * cosi + ni * cost);
	perpe = (ni * cost - nt * cosi) / (ni * cost + nt * cosi);
	return (0.5 * (paral * paral + perpe * perpe));
}

t_tree  *ft_tree_start(t_ray ray, t_obj *o, t_data *data)
{
    t_tree  *node;
    t_pixel p;
    double  l;
    t_ray   rfr;
    double  kr;

    ft_pixel_fill(o, &p, &ray);
    l = ft_lighting(data, &p);
    rfr = ft_refract(ray, o->t, p.normal, o->tpt);
    kr = koef_refr(o->tpt, p.normal, rfr, ray);
    node = ft_tree_new((t_dot){ ray, *o, p.normal, kr, l });
    node->dot.o.color = p.color;
    return (node);
}

int     ft_transparent_colour(t_ray ray, t_obj *o, t_data *data)
{
    t_tree  *node;
    int     colour;
    int     i;
    
    i = 0;
    node = ft_tree_start(ray, o, data);
    if (node == NULL)
    {
        free(node);
        return (BLACK);
    }
    while (i < MAX_DEPTH && node->dot.o.tptp && ft_trace_refracted(node->dot.ray, data, node, &i) != NULL)
        node = node->left;
    colour = ft_traverse_tree(node, i, data);
    ft_free_tree(&node);
    return (colour);
}