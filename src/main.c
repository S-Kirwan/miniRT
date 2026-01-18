/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:23:16 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 17:56:01 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"
#include "window_management.h"

int	main(int argc, char **argv)
{
	t_mlx_data	mlx_data;
	t_ambience	ambience;
	t_mlx_img	mlx_img;
	t_camera	camera;
	t_light		light;
	t_data		data;
	int			scene_fd;

	mlx_data.mlx_img = &mlx_img;
	data.mlx_data = &mlx_data;
	data.ambience = &ambience;
	data.camera = &camera;
	data.light = &light;
	data.shape_list = NULL;
	// if ((scene_fd = validate_file(argc, argv)) == -1)
	// 	return (1);
	// if (receive_scene(&data, scene_fd) == -1)
	// 	return (1);
	initialise_mlx(&mlx_data);
	// print_shape_list(data.shape_list);
	while (1)
		sleep(5);
	return (0);
	(void)argc;
	(void)argv;
	(void)data;
	(void)scene_fd;
}
