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

	ax = (t_vector){all->rt->node->shape->vectors[0], \
		all->rt->node->shape->vectors[1], \
		all->rt->node->shape->vectors[2]};
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

float	calculate_hit_h(t_vector ray_o, t_vector ax, t_vector ray_dir, float t, float *position)
{
	float	hit_h;

	hit_h = (ray_o.x + t * ray_dir.x - position[0]) * ax.x \
		+ (ray_o.y + t * ray_dir.y - position[1]) * ax.y \
		+ (ray_o.z + t * ray_dir.z - position[2]) * ax.z;
	return (hit_h);
}

static int	check_body(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	float		discr;
	float		t0;
	float		t1;
	t_vector	ax;
	float		hit_h;

	array_to_vector(all->rt->node->shape->vectors, &ax);
	origin_to_center(all, ray_o, all->rt->node->shape->position);
	cyl_quad_helper(all, ray_dir, *(all->rt->oc));
	discr = all->rt->qf->b * all->rt->qf->b \
		- 4.0f * all->rt->qf->a * all->rt->qf->c;
	if (discr < 0)
		return (0);
	t0 = (-all->rt->qf->b - sqrtf(discr)) / (2.0f * all->rt->qf->a);
	t1 = (-all->rt->qf->b + sqrtf(discr)) / (2.0f * all->rt->qf->a);
	if (t0 > 0)
	{
		hit_h = calculate_hit_h(ray_o, ax, ray_dir, t0, all->rt->node->shape->position);
		if (hit_h >= 0.0f && hit_h <= all->rt->node->shape->height)
			return (*t = t0, 1);
	}
	if (t1 > 0)
	{
		hit_h = calculate_hit_h(ray_o, ax, ray_dir, t1, all->rt->node->shape->position);
		if (hit_h >= 0.0f && hit_h <= all->rt->node->shape->height)
			return (*t = t1, 1);
	}
	return (0);
}

// d[0] = x d[1] = y d[2] = z, to save lines for norm (temp?)
static int	check_cap(t_data *all, t_vector ray_o, t_vector ray_dir, \
	float *t, float cap_offset)
{
	t_vector	ax;
	t_vector	cap_c;
	float		denom;
	float		tc;
	float		d[3];
	float		rad;

	array_to_vector(all->rt->node->shape->vectors, &ax);
	denom = dot(ray_dir, ax);
	if (fabsf(denom) < 1e-6f)
		return (0);
	cap_c.x = all->rt->node->shape->position[0] + cap_offset * ax.x;
	cap_c.y = all->rt->node->shape->position[1] + cap_offset * ax.y;
	cap_c.z = all->rt->node->shape->position[2] + cap_offset * ax.z;
	tc = ((cap_c.x - ray_o.x) * ax.x + (cap_c.y - ray_o.y) * ax.y \
		+ (cap_c.z - ray_o.z) * ax.z) / denom;
	if (tc <= 0.0f)
		return (0);
	d[0] = ray_o.x + tc * ray_dir.x - cap_c.x;
	d[1] = ray_o.y + tc * ray_dir.y - cap_c.y;
	d[2] = ray_o.z + tc * ray_dir.z - cap_c.z;
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
	if (check_cap(all, ray_o, ray_dir, &t_cap, 0.0f))
		if (!hit || t_cap < *t)
			return (*t = t_cap, 1);
	if (check_cap(all, ray_o, ray_dir, &t_cap, \
		all->rt->node->shape->height))
		if (!hit || t_cap < *t)
			return (*t = t_cap, 1);
	return (hit);
}
