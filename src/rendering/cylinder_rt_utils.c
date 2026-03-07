/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_rt_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 21:17:57 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 21:18:06 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"

void	assign_hit_n(t_vector *hit_n, t_vector ax, int sign)
{
	hit_n->x = ax.x * sign;
	hit_n->y = ax.y * sign;
	hit_n->z = ax.z * sign;
}

void	shape_list_trav_helper_cyl(t_raytracing *rt)
{
	t_vector	ax;
	float		proj;
	float		hit_h;

	rt->closest_t = rt->t_tmp;
	rt->hit_shape = rt->node->shape;
	array_to_vector(rt->node->shape->vectors, &ax);
	calculate_hit_point(rt);
	hit_h = (rt->hit_point->x - rt->node->shape->pos[0]) * ax.x
		+ (rt->hit_point->y - rt->node->shape->pos[1]) * ax.y
		+ (rt->hit_point->z - rt->node->shape->pos[2]) * ax.z;
	if (hit_h < 1e-4f)
		assign_hit_n(rt->hit_n, ax, -1);
	else if (hit_h > rt->node->shape->height - 1e-4f)
		assign_hit_n(rt->hit_n, ax, 1);
	else
	{
		proj = hit_h;
		rt->hit_n->x = rt->hit_point->x - rt->node->shape->pos[0] - proj * ax.x;
		rt->hit_n->y = rt->hit_point->y - rt->node->shape->pos[1] - proj * ax.y;
		rt->hit_n->z = rt->hit_point->z - rt->node->shape->pos[2] - proj * ax.z;
	}
	normalize(rt->hit_n);
}
