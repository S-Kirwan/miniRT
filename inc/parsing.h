/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:28 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 17:46:24 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

typedef struct s_parser
{
	t_list	*shapes;
	int		ambience;
	int		camera;
	int		light;
	int		spheres;
	int		planes;
	int		cylinders;
}	t_parser;

// validate_file.c
int	validate_file(int argc, char **argv);

// receive_scene.c
int	receive_scene(t_data *data, int scene_fd);

// read_ambience.c
void	read_ambience(t_data *data, t_parser *parser, int scene_fd);

// read_camera.c
void	read_camera(t_data *data, t_parser *parser, int scene_fd);

// read_light.c
void	read_light(t_data *data, t_parser *parser, int scene_fd);

// read_plane.c

// read_sphere.c

// read_cylinder.c

#endif

