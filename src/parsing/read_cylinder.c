/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 09:37:25 by skirwan           #+#    #+#             */
/*   Updated: 2026/02/08 15:38:44 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include "raytracing.h"

void	normalise_vector_array(float *vector_array)
{
	t_vector	vector;

	array_to_vector(vector_array, &vector);
	normalize(&vector);
	vector_array[0] = vector.x;
	vector_array[1] = vector.y;
	vector_array[2] = vector.z;
}

int	read_cylinder_data(t_shape *cylinder, char *line)
{
	line = read_coordinates(line, cylinder->position);
	if (line == NULL)
		return (free(cylinder), -1);
	skip_whitespace(&line);
	line = read_vectors(line, cylinder->vectors);
	if (line == NULL)
		return (free(cylinder), -1);
	skip_whitespace(&line);
	line = read_diam_height(line, &cylinder->diameter);
	if (line == NULL)
		return (free(cylinder), -1);
	skip_whitespace(&line);
	line = read_diam_height(line, &cylinder->height);
	if (line == NULL)
		return (free(cylinder), -1);
	skip_whitespace(&line);
	line = read_colours(line, cylinder->colour);
	if (line == NULL)
		return (free(cylinder), -1);
	return (0);
}

void	read_cylinder(t_list **list, t_parser *parser, char *line)
{
	t_shape		*cylinder;

	if (*line != 'y')
		return (parsing_error(&parser->errors));
	line++;
	skip_whitespace(&line);
	cylinder = malloc(sizeof(*cylinder));
	if (cylinder == NULL)
		return (parsing_error(&parser->errors));
	cylinder->shape = CYLINDER;
	if (read_cylinder_data(cylinder, line) == -1)
		return (parsing_error(&parser->errors));
	normalise_vector_array(cylinder->vectors);
	ft_lstadd_back(list, ft_lst_new_shape(cylinder));
	parser->shapes++;
}
