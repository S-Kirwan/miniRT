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

static void	free_helper(t_data *all)
{
	if (all->rt->hit_point)
		free(all->rt->hit_point);
	if (all->rt->light_dir)
		free(all->rt->light_dir);
	if (all->rt->shadow_origin)
		free(all->rt->shadow_origin);
	if (all->rt)
		free(all->rt);
}

void	free_all(t_data *all)
{
	if (all->rt->oc)
		free(all->rt->oc);
	if (all->rt->qf)
		free(all->rt->qf);
	if (all->rt->ray_o)
		free(all->rt->ray_o);
	if (all->rt->forward)
		free(all->rt->forward);
	if (all->rt->right)
		free(all->rt->right);
	if (all->rt->up)
		free(all->rt->up);
	if (all->rt->world_up)
		free(all->rt->world_up);
	if (all->rt->hit_n)
		free(all->rt->hit_n);
	if (all->rt->ray_dir)
		free(all->rt->ray_dir);
	free_helper(all);
}
