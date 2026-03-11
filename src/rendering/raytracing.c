/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 19:43:14 by aramos            #+#    #+#             */
/*   Updated: 2026/03/07 21:14:11 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"

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
*(all->rt->ray_dir), all->rt->node->shape->pos);
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

void	init(t_data *all)
{
	all->camera->fov_rad = all->camera->fov * M_PI / 180.0;
	all->camera->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	all->camera->viewport_h = 2.0 * tan(all->camera->fov_rad / 2.0);
	all->camera->viewport_w = all->camera->viewport_h \
* all->camera->aspect_ratio;
	all->rt = malloc(sizeof(t_raytracing));
	all->rt->oc = malloc(sizeof(t_vector));
	all->rt->qf = malloc(sizeof(t_quad_function));
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
}

int	start_raytracing(t_data *all)
{
	init(all);
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
