/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:28 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/27 16:04:45 by skirwan          ###   ########.fr       */
/*   Updated: 2025/11/25 17:46:24 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include "miniRT.h"

typedef struct s_parser
{
	int			scene_fd;
	int			ambience;
	int			camera;
	int			errors;
	int			light;
}	t_parser;

// validate_file.c
int	validate_file(int argc, char **argv);

// receive_scene.c
int	read_over_spaces(int scene_fd);
int	receive_scene(t_data *data, int scene_fd);

// read_ambience.c
void	read_ambience(t_ambience *ambience, t_parser *parser, char *line);

// read_camera.c
void	read_camera(t_camera *camera, t_parser *parser, char *line);

// read_light.c
void	read_light(t_light *light, t_parser *parser, char *line);

// read_plane.c

// read_sphere.c
void	read_sphere(t_list *list, t_parser *parser, char *line);

// read_cylinder.c

// read_colours.c
char	*read_colours(char *line, int colours[3]);

// read_ratio.c
char	*read_ratio(char *line, float *ratio_ref);

// read_coordinates.c
char	*read_coordinates(char *line, float coordinates[3]);

// read_vectors.c 
char	*read_vectors(char *line, float vectors[3]);

// parsing_utils.c
t_list	*ft_lst_new_shape(t_shape *shape);
char	*read_diameter(char *line, float *diameter);
void	parsing_error(int *errors);
void	print_vectors_test(float vectors[3]);
void	print_colours_test(int colours[3]);
void	print_coords_test(float coords[3]);
int		valid_char_post_element(int i, char c);

//screen.c
void	normalize(t_vector	*v);
#endif

