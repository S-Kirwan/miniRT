/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:23:16 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/06 13:51:07 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

int	main(int argc, char **argv)
{
	t_ambience	ambience;
	t_camera	camera;
	t_light		light;
	t_data		data;
	int			scene_fd;

	data.ambience = &ambience;
	data.camera = &camera;
	data.light = &light;
	data.shape_list = NULL;
	if ((scene_fd = validate_file(argc, argv)) == -1)
		return (1);
	if (receive_scene(&data, scene_fd) == -1)
		return (1);
	// print_shape_list(data.shape_list);
	return (0);
	(void)argc;
	(void)argv;
	(void)data;
	(void)scene_fd;
}
