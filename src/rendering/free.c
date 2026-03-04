/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/04 18:32:09 by aramos            #+#    #+#             */
/*   Updated: 2026/03/04 19:04:26 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"
#include "window_management.h"
#include <stdio.h>

void	free_all(t_data *all)
{
	if (all->rt->oc)
		free(all->rt->oc);
	if (all->rt->qf)
		free(all->rt->qf);// = malloc(sizeof(t_quad_function));
	if (all->rt->ray_o)
		free(all->rt->ray_o);// = malloc(sizeof(t_vector));
	if (all->rt->forward)
		free(all->rt->forward);// = malloc(sizeof(t_vector));
	if (all->rt->right)
		free(all->rt->right);// = malloc(sizeof(t_vector));
	if (all->rt->up)
		free(all->rt->up);// = malloc(sizeof(t_vector));
	if (all->rt->world_up)
		free(all->rt->world_up);// = malloc(sizeof(t_vector));
	if (all->rt->hit_n)
		free(all->rt->hit_n);// = malloc(sizeof(t_vector));
	if (all->rt->ray_dir)
		free(all->rt->ray_dir);// = malloc(sizeof(t_vector));
	if (all->rt->hit_point)
		free(all->rt->hit_point);// = malloc(sizeof(t_vector));
	if (all->rt->light_dir)
		free(all->rt->light_dir);// = malloc(sizeof(t_vector));
	if (all->rt->shadow_origin)
		free(all->rt->shadow_origin);// = malloc(sizeof(t_vector));
	if (all->rt)
		free(all->rt);// = malloc(sizeof(t_raytracing));
}
