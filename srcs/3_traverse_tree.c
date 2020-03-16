/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_traverse_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pberge <pberge@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 01:33:13 by pberge            #+#    #+#             */
/*   Updated: 2020/02/29 06:14:12 by pberge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

// /*
// **  tracing refracted ray
// **  if it hits objects, saving new dot to tree
// */

t_tree  *ft_trace_refracted(t_ray ray, t_data *data, t_tree *node, int *i)
{
    t_obj   *o;
    t_ray   rfr;
    t_pixel p;
    double  kr;
    double  l;

    rfr = ft_refract(ray, node->dot.o.t, node->dot.norm, node->dot.o.tpt);
    o = ft_obj_intersect(data->obj_all, &rfr, SHADOW_OFF);
    if (o == NULL)
        return (NULL);
    (*i)++;
    ft_pixel_fill(o, &p, &rfr);
    l = ft_lighting(data, &p);
    if (o->tptp > 0)
    {
        ray = rfr;
        rfr = ft_refract(ray, o->t, p.normal, o->tpt);
        kr = koef_refr(o->tpt, p.normal, rfr, ray);
        node->left = ft_tree_new((t_dot){ ray, *o, p.normal, kr, l });
    }
    else
       node->left = ft_tree_new((t_dot){ rfr, *o, p.normal, 1., l });
    node->left->dot.o.color = p.color;
    node->left->parent = node;
    return (node->left);
}

t_tree  *ft_trace_reflected(t_ray ray, t_data *data, t_tree *node, int *i)
{
    t_obj   *o;
    t_ray   lect;
    t_pixel p;
    double  kr;
    double  l;
    t_ray   rfr;

    lect = ft_reflect(ray, node->dot.o.t, node->dot.norm);
    o = ft_obj_intersect(data->obj_all, &lect, SHADOW_OFF);
    if (o == NULL)
        return (NULL);
    (*i)++;
    ft_pixel_fill(o, &p, &lect);
    l = ft_lighting(data, &p);
    if (o->tptp > 0)
    {
        rfr = ft_refract(lect, o->t, p.normal, o->tpt);
        kr = koef_refr(o->tpt, p.normal, rfr, lect);
        node->right = ft_tree_new((t_dot){ lect, *o, p.normal, kr, l });
    }
    else
        node->right = ft_tree_new((t_dot){ lect, *o, p.normal, 1., l});
    node->right->dot.o.color = p.color;
    node->right->parent = node;
    return (node->right);
}

void    ft_left_colour(t_tree *node)
{
    t_dot   dot;

    dot = node->dot;
    if (node->left == NULL)
        node->left_col = ft_rgb(BACKGROUND);
    else
        node->left_col = node->left->colour;
    if (dot.o.tptp > 0)
        node->left_col = ft_rgb_add(
                ft_multiply_color(dot.o.tptp, node->left_col, 0),
                ft_multiply_color((1. - dot.o.tptp) * dot.l, dot.o.color,
                                    dot.o.specular));
    else
        node->left_col = ft_multiply_color(dot.l, dot.o.color,
                                                dot.o.specular);
}

void    ft_right_colour(t_tree *node)
{
    t_dot   dot;

    dot = node->dot;
    if (node->right == NULL)
        node->right_col = ft_rgb(BACKGROUND);
    else
        node->right_col = node->right->colour;
    if (dot.o.tptp > 0)
        node->colour = ft_rgb_add(
                        ft_multiply_color(dot.kr, node->right_col, 0),
                        ft_multiply_color(1. - dot.kr, node->left_col, 0));
    else
        node->colour = node->left_col;
}

int     ft_traverse_tree(t_tree *node, int i, t_data *data)
{
    while (node != NULL)
    {
        ft_left_colour(node);
        if (i < MAX_DEPTH && node->dot.o.tptp && ft_trace_reflected(node->dot.ray, data, node, &i) != NULL)
        {
            node = node->right;
            while (i < MAX_DEPTH && node->dot.o.tptp && ft_trace_refracted(node->dot.ray, data, node, &i) != NULL)
                node = node->left;
        }
        else
        {
            while (node->parent != NULL && node->parent->right == node)
            {
                ft_right_colour(node);
                node = node->parent;
                i--;
            }
            ft_right_colour(node);
            if (node->parent == NULL)
                break ;
            node = node->parent;
            i--;
        }
    }
    return (node->colour);
}