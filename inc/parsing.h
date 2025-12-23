/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:28 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/15 11:54:58 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

/*
typedef enum e_bad_reads
{
	READ_ERROR = -1,
	END_OF_FILE = -2,
	INVALID_CHARACTER = -3,
} t_bad_reads;
may not use this enum
*/

typedef struct s_parser
{
	t_list	*shapes;
	int		scene_fd;
	int		ambience;
	int		camera;
	int		light;
	int		spheres;
	int		planes;
	int		cylinders;
	int		errors;
}	t_parser;

// validate_file.c
int	validate_file(int argc, char **argv);

// receive_scene.c
int	read_over_spaces(int scene_fd);
int	receive_scene(t_data *data, int scene_fd);

// read_ambience.c
void	read_ambience(t_ambience *ambience, t_parser *parser, char *line);

// read_camera.c
void	read_camera(t_data *data, t_parser *parser, char *line);

// read_light.c
void	read_light(t_data *data, t_parser *parser, char *line);

// read_plane.c

// read_sphere.c

// read_cylinder.c

// read_colours.c
void	print_colours_test(int colours[3]);
int		read_colours(char *line, int colours[3]);

#endif

