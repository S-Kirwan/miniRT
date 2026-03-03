/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:53:24 by aramos            #+#    #+#             */
/*   Updated: 2026/03/03 19:53:50 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

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
