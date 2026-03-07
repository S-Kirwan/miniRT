/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cylinder_body.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 22:34:54 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 22:36:36 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/raytracing.h"
#include <math.h>

static void	cyl_quad_helper(t_data *all, t_vector ray_dir, t_vector oc)
{
	t_vector	ax;
	t_vector	dp;
	t_vector	op;
	float		rad;

	array_to_vector(all->rt->node->shape->vectors, &ax);
	dp.x = ray_dir.x - dot(ray_dir, ax) * ax.x;
	dp.y = ray_dir.y - dot(ray_dir, ax) * ax.y;
	dp.z = ray_dir.z - dot(ray_dir, ax) * ax.z;
	op.x = oc.x - dot(oc, ax) * ax.x;
	op.y = oc.y - dot(oc, ax) * ax.y;
	op.z = oc.z - dot(oc, ax) * ax.z;
	rad = all->rt->node->shape->diameter / 2.0f;
	all->rt->qf->a = dot(dp, dp);
	all->rt->qf->b = 2.0f * dot(dp, op);
	all->rt->qf->c = dot(op, op) - rad * rad;
}

static float	calculate_hit_h(t_vector ax, t_raytracing *rt, float t)
{
	float	hit_h;

	hit_h = (rt->ray_o->x + t * rt->ray_dir->x - rt->node->shape->pos[0]) * ax.x
		+ (rt->ray_o->y + t * rt->ray_dir->y - rt->node->shape->pos[1]) * ax.y
		+ (rt->ray_o->z + t * rt->ray_dir->z - rt->node->shape->pos[2]) * ax.z;
	return (hit_h);
}

int	calculate_discr(t_raytracing *rt, float *discr)
{
	*discr = rt->qf->b * rt->qf->b
		- 4.0f * rt->qf->a * rt->qf->c;
	if (*discr < 0)
		return (-1);
	return (0);
}

int	check_body_helper(t_data *all, float *t, t_vector ax, float t_var)
{
	float		hit_h;

	if (t_var > 0)
	{
		hit_h = calculate_hit_h(ax, all->rt, t_var);
		if (hit_h >= 0.0f && hit_h <= all->rt->node->shape->height)
			return (*t = t_var, 1);
	}
	return (0);
}

int	check_body(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	float		discr;
	float		t0;
	float		t1;
	t_vector	ax;

	array_to_vector(all->rt->node->shape->vectors, &ax);
	origin_to_center(all, ray_o, all->rt->node->shape->pos);
	cyl_quad_helper(all, ray_dir, *(all->rt->oc));
	if (calculate_discr(all->rt, &discr) < 0)
		return (0);
	t0 = (-all->rt->qf->b - sqrtf(discr)) / (2.0f * all->rt->qf->a);
	t1 = (-all->rt->qf->b + sqrtf(discr)) / (2.0f * all->rt->qf->a);
	if (t0 > 0)
		return (check_body_helper(all, t, ax, t0));
	else if (t1 > 0)
		return (check_body_helper(all, t, ax, t1));
	return (0);
}
