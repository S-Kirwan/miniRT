/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:52:43 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 21:15:34 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

void	read_sphere(t_list **list, t_parser *parser, char *line)
{
	t_shape	*sphere;

	if (*line != 'p')
		return (parsing_error(&parser->errors, "shape name"));
	line++;
	skip_whitespace(&line);
	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		return (parsing_error(&parser->errors, "Bad malloc"));
	sphere->shape = SPHERE;
	line = read_coordinates(line, sphere->pos);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors,
				"sphere coordinates"));
	skip_whitespace(&line);
	line = read_diam_height(line, &sphere->diameter);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors, "sphere height"));
	skip_whitespace(&line);
	line = read_colours(line, sphere->colour);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors,
				"sphere colours"));
	ft_lstadd_back(list, ft_lst_new_shape(sphere));
	parser->shapes++;
}
