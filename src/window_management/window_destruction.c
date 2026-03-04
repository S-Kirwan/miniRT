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

int	full_exit(t_mlx_data *mlx_data)
{
	mlx_destroy_image(mlx_data->mlx_instance, mlx_data->mlx_img->image);
	mlx_destroy_window(mlx_data->mlx_instance, mlx_data->window);
	mlx_destroy_display(mlx_data->mlx_instance);
	free(mlx_data->mlx_instance);
	free(mlx_data->mlx_img);
	free(mlx_data);
	exit (0);
}

int	key_press_event(int keycode, t_data *all)//, t_mlx_data *mlx_data)
{
	if (keycode == ESC)
	{
		free_all(all);
		full_exit(all->mlx_data);
	}
	return (0);
}
