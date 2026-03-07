/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:56:55 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 21:15:19 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/raytracing.h"
#include <math.h>

static float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

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

static int	check_body(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
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

// d[0] = x d[1] = y d[2] = z, to save lines for norm (temp?)
static int	check_cap(t_data *all, float *t, float cap_offset)
{
	t_vector	ax;
	t_vector	cap_c;
	float		tc;
	float		d[3];
	float		rad;

	array_to_vector(all->rt->node->shape->vectors, &ax);
	all->rt->denom = dot(*all->rt->ray_dir, ax);
	if (fabsf(all->rt->denom) < 1e-6f)
		return (0);
	cap_c.x = all->rt->node->shape->pos[0] + cap_offset * ax.x;
	cap_c.y = all->rt->node->shape->pos[1] + cap_offset * ax.y;
	cap_c.z = all->rt->node->shape->pos[2] + cap_offset * ax.z;
	tc = ((cap_c.x - all->rt->ray_o->x) * ax.x + (cap_c.y - \
all->rt->ray_o->y) * ax.y + (cap_c.z - all->rt->ray_o->z) * ax.z) \
/ all->rt->denom;
	if (tc <= 0.0f)
		return (0);
	d[0] = all->rt->ray_o->x + tc * all->rt->ray_dir->x - cap_c.x;
	d[1] = all->rt->ray_o->y + tc * all->rt->ray_dir->y - cap_c.y;
	d[2] = all->rt->ray_o->z + tc * all->rt->ray_dir->z - cap_c.z;
	rad = all->rt->node->shape->diameter / 2.0f;
	if (d[0] * d[0] + d[1] * d[1] + d[2] * d[2] > rad * rad)
		return (0);
	return (*t = tc, 1);
}

int	cylinder_hit(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	float	t_body;
	float	t_cap;
	int		hit;

	hit = 0;
	if (check_body(all, ray_o, ray_dir, &t_body))
	{
		*t = t_body;
		hit = 1;
	}
	if (check_cap(all, &t_cap, 0.0f))
		if (!hit || t_cap < *t)
			return (*t = t_cap, 1);
	if (check_cap(all, &t_cap, all->rt->node->shape->height))
		if (!hit || t_cap < *t)
			return (*t = t_cap, 1);
	return (hit);
}
