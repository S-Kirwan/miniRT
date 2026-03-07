#include "../inc/miniRT.h"
#include "../inc/raytracing.h"
#include <math.h>

/* Dot product of two vectors */
static float	dot(t_vector a, t_vector b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
** Fills all->rt->qf with the quadratic coefficients for the cylinder body.
** Projects ray_dir and oc onto the plane perpendicular to the cylinder axis,
** then solves the 2D circle intersection in that projected space.
*/
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

/*
** Tests the curved body of the cylinder.
** Checks that each candidate t places the hit point within [0, height]
** along the cylinder axis before accepting it.
*/
static int	check_body(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	float		discr;
	float		t0;
	float		t1;
	t_vector	ax;
	float		hit_h;

	ax = (t_vector){all->rt->node->shape->vectors[0], \
		all->rt->node->shape->vectors[1], \
		all->rt->node->shape->vectors[2]};
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
		hit_h = (ray_o.x + t0 * ray_dir.x - all->rt->node->shape->position[0]) \
			* ax.x + (ray_o.y + t0 * ray_dir.y - all->rt->node->shape->position[1]) \
			* ax.y + (ray_o.z + t0 * ray_dir.z - all->rt->node->shape->position[2]) \
			* ax.z;
		if (hit_h >= 0.0f && hit_h <= all->rt->node->shape->height)
			return (*t = t0, 1);
	}
	if (t1 > 0)
	{
		hit_h = (ray_o.x + t1 * ray_dir.x - all->rt->node->shape->position[0]) \
			* ax.x + (ray_o.y + t1 * ray_dir.y - all->rt->node->shape->position[1]) \
			* ax.y + (ray_o.z + t1 * ray_dir.z - all->rt->node->shape->position[2]) \
			* ax.z;
		if (hit_h >= 0.0f && hit_h <= all->rt->node->shape->height)
			return (*t = t1, 1);
	}
	return (0);
}

/*
** Tests one end cap (a disc) of the cylinder.
** cap_offset = 0.0f for the base cap, shape->height for the top cap.
** Finds where the ray hits the cap's plane, then checks the hit point
** lies within the disc radius.
*/
static int	check_cap(t_data *all, t_vector ray_o, t_vector ray_dir, \
	float *t, float cap_offset)
{
	t_vector	ax;
	t_vector	cap_c;
	float		denom;
	float		tc;
	float		dx;
	float		dy;
	float		dz;
	float		rad;

	ax = (t_vector){all->rt->node->shape->vectors[0], \
		all->rt->node->shape->vectors[1], \
		all->rt->node->shape->vectors[2]};
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
	dx = ray_o.x + tc * ray_dir.x - cap_c.x;
	dy = ray_o.y + tc * ray_dir.y - cap_c.y;
	dz = ray_o.z + tc * ray_dir.z - cap_c.z;
	rad = all->rt->node->shape->diameter / 2.0f;
	if (dx * dx + dy * dy + dz * dz > rad * rad)
		return (0);
	return (*t = tc, 1);
}

/*
** Main cylinder hit function. Tests both the curved body and the two end
** caps, returning the smallest positive t (i.e. the closest hit to camera).
** Returns 1 if the ray hits the cylinder, 0 otherwise.
*/
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
