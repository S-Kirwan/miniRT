/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/07 20:56:55 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 22:36:51 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/raytracing.h"
#include <math.h>

float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
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
