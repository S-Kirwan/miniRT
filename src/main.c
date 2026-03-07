/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:23:16 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/04 18:51:10 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "parsing.h"
#include "data_management.h"
#include "raytracing.h"
#include "window_management.h"

int	main(int argc, char **argv)
{
	t_data		*data;
	int			scene_fd;

	scene_fd = validate_file(argc, argv);
	if (scene_fd == -1)
		return (1);
	if (initialise_data(&data) == -1)
		return (1);
	if (receive_scene(data, scene_fd) == -1)
		return (1);
	initialise_mlx(data);//, data->mlx_data);
	start_raytracing(data);
	mlx_put_image_to_window(data->mlx_data->mlx_instance, data->mlx_data->window, data->mlx_data->mlx_img->image, 0, 0);
	mlx_loop(data->mlx_data->mlx_instance);
	return (0);
}
