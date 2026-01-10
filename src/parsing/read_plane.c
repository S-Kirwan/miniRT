/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 12:41:53 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/02 12:54:34 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"
#include "libft.h"
#include <stdio.h>

void	read_plane(t_list **list, t_parser *parser, char *line)
{
	t_shape	*plane;

	if (*line != 'l')
		return (parsing_error(&parser->errors));
	line++;
	skip_whitespace(&line);
	plane = malloc(sizeof(*plane));
	if (plane == NULL)
		return (parsing_error(&parser->errors));
	plane->shape = PLANE;
	line = read_coordinates(line, plane->position);
	if (line == NULL)
		return (free(plane), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_vectors(line, plane->vectors);
	if (line == NULL)
		return (free(plane), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_colours(line, plane->colour);
	if (line == NULL)
		return (free(plane), parsing_error(&parser->errors));
	ft_lstadd_back(list, ft_lst_new_shape(plane));
}
