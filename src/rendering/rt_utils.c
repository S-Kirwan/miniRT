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

void	shape_list_trav_helper_cyl(t_raytracing *rt, t_vector ray_dir)
{
	t_vector	ax;
	t_vector	hp;
	float		proj;
	float		hit_h;

	rt->closest_t = rt->t_tmp;
	rt->hit_shape = rt->node->shape;
	ax.x = rt->node->shape->vectors[0];
	ax.y = rt->node->shape->vectors[1];
	ax.z = rt->node->shape->vectors[2];
	hp.x = rt->ray_o->x + rt->t_tmp * ray_dir.x;
	hp.y = rt->ray_o->y + rt->t_tmp * ray_dir.y;
	hp.z = rt->ray_o->z + rt->t_tmp * ray_dir.z;
	hit_h = (hp.x - rt->node->shape->position[0]) * ax.x \
		+ (hp.y - rt->node->shape->position[1]) * ax.y \
		+ (hp.z - rt->node->shape->position[2]) * ax.z;
	if (hit_h < 1e-4f)
	{
		rt->hit_n->x = -ax.x;
		rt->hit_n->y = -ax.y;
		rt->hit_n->z = -ax.z;
	}
	else if (hit_h > rt->node->shape->height - 1e-4f)
	{
		rt->hit_n->x = ax.x;
		rt->hit_n->y = ax.y;
		rt->hit_n->z = ax.z;
	}
	else
	{
		proj = hit_h;
		rt->hit_n->x = hp.x - rt->node->shape->position[0] - proj * ax.x;
		rt->hit_n->y = hp.y - rt->node->shape->position[1] - proj * ax.y;
		rt->hit_n->z = hp.z - rt->node->shape->position[2] - proj * ax.z;
	}
	normalize(rt->hit_n);
}

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

void	shape_list_trav_helper(t_raytracing *rt, t_vector ray_dir, float pos[3])
{
	rt->closest_t = rt->t_tmp;
	rt->hit_shape = rt->node->shape;
	rt->hit_n->x = rt->ray_o->x + rt->t_tmp * ray_dir.x - pos[0];
	rt->hit_n->y = rt->ray_o->y + rt->t_tmp * ray_dir.y - pos[1];
	rt->hit_n->z = rt->ray_o->z + rt->t_tmp * ray_dir.z - pos[2];
	normalize(rt->hit_n);
}

void	shape_list_traversal(t_raytracing *rt, t_vector ray_dir, float pos[3])
{
	if (rt->node->shape->shape == SPHERE)
	{
		if (sphere_hit(rt->all, *(rt->ray_o), \
ray_dir, &rt->t_tmp) && rt->t_tmp < rt->closest_t)
			shape_list_trav_helper(rt, ray_dir, pos);
	}
	else if (rt->node->shape->shape == PLANE)
	{
		if (plane_hit(rt->node->shape, *(rt->ray_o), \
ray_dir, &rt->t_tmp) && rt->t_tmp < rt->closest_t)
		{
			rt->closest_t = rt->t_tmp;
			rt->hit_shape = rt->node->shape;
			rt->hit_n->x = rt->node->shape->vectors[0];
			rt->hit_n->y = rt->node->shape->vectors[1];
			rt->hit_n->z = rt->node->shape->vectors[2];
			normalize(rt->hit_n);
		}
	}
	else if (rt->node->shape->shape == CYLINDER)
	{
		if (cylinder_hit(rt->all, *(rt->ray_o), ray_dir, &rt->t_tmp)
			&& rt->t_tmp < rt->closest_t)
			shape_list_trav_helper_cyl(rt, ray_dir);

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
