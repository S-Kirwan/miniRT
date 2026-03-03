/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 20:12:04 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 20:12:28 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

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
