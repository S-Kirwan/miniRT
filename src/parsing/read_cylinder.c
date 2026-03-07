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

void	read_cylinder(t_list **list, t_parser *parser, char *line)
{
	t_shape		*cylinder;
	t_vector	vector;

	if (*line != 'y')
		return (parsing_error(&parser->errors));
	line++;
	skip_whitespace(&line);
	cylinder = malloc(sizeof(*cylinder));
	if (cylinder == NULL)
		return (parsing_error(&parser->errors));
	cylinder->shape = CYLINDER;
	line = read_coordinates(line, cylinder->position);
	if (line == NULL)
		return (free(cylinder), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_vectors(line, cylinder->vectors);
	if (line == NULL)
		return (free(cylinder), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_diam_height(line, &cylinder->diameter);
	if (line == NULL)
		return (free(cylinder), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_diam_height(line, &cylinder->height);
	if (line == NULL)
		return (free(cylinder), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_colours(line, cylinder->colour);
	if (line == NULL)
		return (free(cylinder), parsing_error(&parser->errors));
	array_to_vector(cylinder->vectors, &vector);
	normalize(&vector);
	cylinder->vectors[0] = vector.x;
	cylinder->vectors[1] = vector.y;
	cylinder->vectors[2] = vector.z;
	ft_lstadd_back(list, ft_lst_new_shape(cylinder));
	parser->shapes++;
}
