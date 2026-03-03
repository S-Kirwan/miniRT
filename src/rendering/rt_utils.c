/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:53:41 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 20:20:53 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

void	array_to_vector(float source[3], t_vector *dest)
{
	dest->x = source[0];
	dest->y = source[1];
	dest->z = source[2];
}

void	get_world_up(t_data *all)
{
	if (fabs(all->rt->forward->y) > 0.999)
	{
		all->rt->world_up->x = 1;
		all->rt->world_up->y = 0;
		all->rt->world_up->z = 0;
	}
	else
	{
		all->rt->world_up->x = 0;
		all->rt->world_up->y = 1;
		all->rt->world_up->z = 0;
	}
}

void	shape_list_traversal(t_raytracing *rt, t_vector ray_dir, float pos[3])
{
	if (rt->node->shape->shape == SPHERE)
	{
		if (sphere_hit(rt->all, *(rt->ray_o), ray_dir, &rt->t_tmp) && rt->t_tmp < rt->closest_t)
		{
			rt->closest_t = rt->t_tmp;
			rt->hit_shape = rt->node->shape;
			rt->hit_n->x = rt->ray_o->x + rt->t_tmp * ray_dir.x - pos[0];
			rt->hit_n->y = rt->ray_o->y + rt->t_tmp * ray_dir.y - pos[1];
			rt->hit_n->z = rt->ray_o->z + rt->t_tmp * ray_dir.z - pos[2];
			normalize(rt->hit_n);
		}
	}
	else if (rt->node->shape->shape == PLANE)
	{
		if (plane_hit(rt->node->shape, *(rt->ray_o), ray_dir, &rt->t_tmp) && rt->t_tmp < rt->closest_t)
		{
			rt->closest_t = rt->t_tmp;
			rt->hit_shape = rt->node->shape;
			rt->hit_n->x = rt->node->shape->vectors[0];
			rt->hit_n->y = rt->node->shape->vectors[1];
			rt->hit_n->z = rt->node->shape->vectors[2];
			normalize(rt->hit_n);
		}
	}
	rt->node = rt->node->next;
}

void	hit_helper(t_data *all, int x, int y)
{
	calculate_hit_point(all->rt);
	calculate_light_dir(all);
	calculate_shadow_origin(all->rt);
	all->rt->node = all->shape_list;
	throw_shade(all);
	calculte_diffuse(all, all->rt->in_shadow);
	color_pixel(all, x, y);
}
