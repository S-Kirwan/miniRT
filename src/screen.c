/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:53:41 by aramos            #+#    #+#             */
/*   Updated: 2026/02/21 16:29:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

// #define WIDTH 500
// #define HEIGHT 500

//oc is the distance between the origin ray 
//(camera vector) and the center of the sphere
//that means that oc is equal to (O - C)
int	sphere_hit(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	t_vector  oc;

	all->rt->oc->x = ray_o.x - all->rt->node->shape->position[0];
  all->rt->oc->y = ray_o.y - all->rt->node->shape->position[1];
  all->rt->oc->z = ray_o.z - all->rt->node->shape->position[2];
  oc = *(all->rt->oc);
	float		a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	float		b = 2.0f * (oc.x * ray_dir.x + oc.y * ray_dir.y + oc.z * ray_dir.z);
	float		c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (all->rt->node->shape->diameter / 2.0f) * (all->rt->node->shape->diameter / 2.0f); 
	float		discriminant = b * b - 4 * a * c;
	float		t0;
	float		t1;

	if (discriminant < 0)
		return (0);
	t0 = (-b - sqrt(discriminant)) / (2.0f * a);
	t1 = (-b + sqrt(discriminant)) / (2.0f * a);
	if (t0 > 0)
		*t = t0;
	else if (t1 > 0)
		*t = t1;
	else
		return (0);
	return (1);
}

//N * (P-P0) = 0
//formula for the plane.
//N is the normalized vector used to check if anything is perpendicular to it
int	plane_hit(t_shape *plane, t_vector ray_o, t_vector ray_dir, float *t)
{
	float		denom;
	t_vector	p0;

	denom = plane->vectors[0] * ray_dir.x \
+ plane->vectors[1] * ray_dir.y \
+ plane->vectors[2] * ray_dir.z;
	if (fabs(denom) < 1e-6)
		return (0);
	p0.x = plane->position[0] - ray_o.x;
	p0.y = plane->position[1] - ray_o.y;
	p0.z = plane->position[2] - ray_o.z;
	*t = p0.x * plane->vectors[0] + p0.y \
* plane->vectors[1] + p0.z * plane->vectors[2];
	*t /= denom;
	return (*t > 0);
}

void	array_to_vector(float source[3], t_vector *dest)
{
	dest->x = source[0];
	dest->y = source[1];
	dest->z = source[2];
}

void	cross_product(t_vector *a, t_vector *b, t_vector *result, int up)
{
	result->x = a->y * b->z - a->z * b->y;
	if (!up)
	{
		result->y = a->x * b->z - a->x * b->z;
		result->z = a->x * b->y - a->x * b->y;
	}
	else if (up == 1)
	{
		result->y = a->z * b->x - a->x * b->z;
		result->z = a->x * b->y - a->y * b->x;
	}
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

void	calculate_offset(t_data *all, t_raytracing *rt, int x, int y)
{
	float	u;
	float	v;

	u = ((x + 0.5f) / WIDTH - 0.5f) * all->camera->viewport_w;
	v = ((y + 0.5f) / HEIGHT - 0.5f) * all->camera->viewport_h;
	rt->ray_dir->x = rt->forward->x + u * rt->right->x + v * rt->up->x;
	rt->ray_dir->y = rt->forward->y + u * rt->right->y + v * rt->up->y;
	rt->ray_dir->z = rt->forward->z + u * rt->right->z + v * rt->up->z;
	normalize(rt->ray_dir);
	rt->closest_t = 1e30;
	rt->hit_shape = NULL;
	rt->node = all->shape_list;
}

void	calculate_hit_point(t_raytracing *rt)
{
	rt->hit_point->x = rt->ray_o->x + rt->closest_t * rt->ray_dir->x;
	rt->hit_point->y = rt->ray_o->y + rt->closest_t * rt->ray_dir->y;
	rt->hit_point->z = rt->ray_o->z + rt->closest_t * rt->ray_dir->z;
}

void	calculate_light_dir(t_data *all)
{
	all->rt->light_dir->x = all->light->position[0] - all->rt->hit_point->x;
	all->rt->light_dir->y = all->light->position[1] - all->rt->hit_point->y;
	all->rt->light_dir->z = all->light->position[2] - all->rt->hit_point->z;
	all->rt->light_distance = sqrt(all->rt->light_dir->x \
* all->rt->light_dir->x + all->rt->light_dir->y * all->rt->light_dir->y \
+ all->rt->light_dir->z * all->rt->light_dir->z);
	normalize(all->rt->light_dir);
}

void	calculate_shadow_origin(t_raytracing *rt)
{
	rt->shadow_origin->x = rt->hit_point->x + rt->hit_n->x * 0.001f;
	rt->shadow_origin->y = rt->hit_point->y + rt->hit_n->y * 0.001f;
	rt->shadow_origin->z = rt->hit_point->z + rt->hit_n->z * 0.001f;
	rt->in_shadow = 0;
}

void	calculte_diffuse(t_data *all, int in_shadow)
{
	all->rt->diffuse = all->rt->hit_n->x * all->rt->light_dir->x \
+ all->rt->hit_n->y * all->rt->light_dir->y \
+ all->rt->hit_n->z * all->rt->light_dir->z;
	all->rt->shadow_factor = 1.0f;
	if (all->rt->diffuse < 0)
		all->rt->diffuse = 0;
	if (in_shadow)
		all->rt->shadow_factor = 0.3f;
	all->rt->diffuse *= all->light->brightness * all->rt->shadow_factor;
}

void	color_pixel(t_data *all, int x, int y)
{
	float	intensity;
	int		color;
	int		r;
	int		g;
	int		b;

	intensity = all->ambience->ratio + all->rt->diffuse;
	if (intensity > 1.0f)
		intensity = 1.0f;
	r = (int)(all->rt->hit_shape->colour[0] * intensity);
	g = (int)(all->rt->hit_shape->colour[1] * intensity);
	b = (int)(all->rt->hit_shape->colour[2] * intensity);
	color = (r << 16) | (g << 8) | b;
	place_pixel_to_img(all->mlx_data->mlx_img, x, y, color);
}

void	throw_shade(t_data *all)
{
	float	shadow_t;

	while (all->rt->node)
	{
		if ((all->rt->node->shape->shape == SPHERE \
&& sphere_hit(all, *(all->rt->shadow_origin), \
*(all->rt->light_dir), &shadow_t) && shadow_t < all->rt->light_distance) || \
(all->rt->node->shape->shape == PLANE \
&& plane_hit(all->rt->node->shape, *(all->rt->shadow_origin), \
*(all->rt->light_dir), &shadow_t) && shadow_t < all->rt->light_distance))
		{
			all->rt->in_shadow = 1;
			break ;
		}
		all->rt->node = all->rt->node->next;
	}
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

void	raytracing(t_data *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			calculate_offset(all, all->rt, x, y);
			while (all->rt->node)
			{
				shape_list_traversal(all->rt, \
*(all->rt->ray_dir), all->rt->node->shape->position);
			}
			if (all->rt->hit_shape)
				hit_helper(all, x, y);
			else
				place_pixel_to_img(all->mlx_data->mlx_img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

//Normalizes a vector which has to have x y and z values already.
//It modifies it dirrectly, so a pointer is needed.
//And is better to have a t_vector type in the
//struct to be able to access the original info if needed
void	normalize(t_vector	*v)
{
	float	len;

	len = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	if (len == 0)
		return ;
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

int	start_raytracing(t_data *all)
{
	all->camera->fov_rad = all->camera->fov * M_PI / 180.0;
	all->camera->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	all->camera->viewport_h = 2.0 * tan(all->camera->fov_rad / 2.0);
	all->camera->viewport_w = all->camera->viewport_h \
* all->camera->aspect_ratio;
	all->rt = malloc(sizeof(t_raytracing));
	all->rt->oc = malloc(sizeof(t_vector));
	all->rt->all = all;
	all->rt->ray_o = malloc(sizeof(t_vector));
	all->rt->forward = malloc(sizeof(t_vector));
	all->rt->right = malloc(sizeof(t_vector));
	all->rt->up = malloc(sizeof(t_vector));
	all->rt->world_up = malloc(sizeof(t_vector));
	all->rt->hit_n = malloc(sizeof(t_vector));
	all->rt->ray_dir = malloc(sizeof(t_vector));
	all->rt->hit_point = malloc(sizeof(t_vector));
	all->rt->light_dir = malloc(sizeof(t_vector));
	all->rt->shadow_origin = malloc(sizeof(t_vector));
	all->rt->node = all->shape_list;
	array_to_vector(all->camera->position, all->rt->ray_o);
	array_to_vector(all->camera->orientation, all->rt->forward);
	get_world_up(all);
	cross_product(all->rt->world_up, all->rt->forward, all->rt->right, 0);
	cross_product(all->rt->right, all->rt->forward, all->rt->up, 1);
	normalize(all->rt->right);
	normalize(all->rt->up);
	raytracing(all);
	return (0);
}
