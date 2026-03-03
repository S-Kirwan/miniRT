/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:51:49 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 19:52:33 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

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
