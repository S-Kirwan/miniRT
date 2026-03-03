/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:56:58 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 20:11:40 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

void	origin_to_center(t_data *all, t_vector ray_o, float *position)
{
	all->rt->oc->x = ray_o.x - position[0];
	all->rt->oc->y = ray_o.y - position[1];
	all->rt->oc->z = ray_o.z - position[2];
}

float	quadratic_function(float a, float b, float c)
{
	return (b * b - 4 * a * c);
}

//oc is the distance between the origin ray 
//(camera vector) and the center of the sphere
//that means that oc is equal to (O - C)
int	sphere_hit(t_data *all, t_vector ray_o, t_vector ray_dir, float *t)
{
	float		t0;
	float		t1;
	t_vector	oc;
	float		discriminant;

	origin_to_center(all, ray_o, all->rt->node->shape->position);
	oc = *(all->rt->oc);
	all->rt->qf->a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	all->rt->qf->b = 2.0f * (oc.x * ray_dir.x + oc.y * ray_dir.y + oc.z * ray_dir.z);
	all->rt->qf->c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (all->rt->node->shape->diameter / 2.0f) * (all->rt->node->shape->diameter / 2.0f); 
	// b * b - 4 * a * c;
	discriminant = quadratic_function(all->rt->qf->a, all->rt->qf->b, all->rt->qf->c);

	if (discriminant < 0)
		return (0);
	t0 = (-all->rt->qf->b - sqrt(discriminant)) / (2.0f * all->rt->qf->a);
	t1 = (-all->rt->qf->b + sqrt(discriminant)) / (2.0f * all->rt->qf->a);
	if (t0 > 0)
		*t = t0;
	else if (t1 > 0)
		*t = t1;
	else
		return (0);
	return (1);
}
