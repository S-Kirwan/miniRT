/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_initialisation.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:55:18 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/04 18:52:48 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"

void	initialise_mlx(t_data *all)//, t_mlx_data *mlx_data)
{
	t_mlx_data	*mlx_data;

	mlx_data = all->mlx_data;
	mlx_data->mlx_instance = mlx_init();
	mlx_data->window = mlx_new_window(mlx_data->mlx_instance, WIDTH, HEIGHT, "miniRT");
	create_mlx_img(mlx_data->mlx_img, mlx_data->mlx_instance);
	// mlx_put_image_to_window(mlx_data->mlx_instance, mlx_data->window, mlx_data->mlx_img, 0, 0);
	close_window_hooks(all);
}
