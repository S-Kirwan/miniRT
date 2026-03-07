/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_destruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:20:54 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/04 18:59:37 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"
#include "raytracing.h"
#include <stdlib.h>

void	free_capital_structs(t_data *all)
{
	free(all->ambience);
	free(all->camera);
	free(all->light);
}

void	free_shape_list(t_data *all)
{
	t_list	*traverser;
	t_list	*temp;

	traverser = all->shape_list;
	while (traverser != NULL)
	{
		temp = traverser;
		traverser = traverser->next;
		free(temp->shape);
		free(temp);
	}
}

int	full_exit(t_data *all)
{
	t_mlx_data *mlx_data;

	mlx_data = all->mlx_data;
	mlx_destroy_image(mlx_data->mlx_instance, mlx_data->mlx_img->image);
	mlx_destroy_window(mlx_data->mlx_instance, mlx_data->window);
	mlx_destroy_display(mlx_data->mlx_instance);
	free(mlx_data->mlx_instance);
	free(mlx_data->mlx_img);
	free(mlx_data);
	free_shape_list(all);
	free_all(all);
	free_capital_structs(all);
	free(all);
	exit (0);
}

int	key_press_event(int keycode, t_data *all)
{
	if (keycode == ESC)
	{
		full_exit(all);
	}
	return (0);
}
