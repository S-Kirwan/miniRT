/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:48:48 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 19:56:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

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
