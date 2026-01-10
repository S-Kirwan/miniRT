/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_sphere.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 11:52:43 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/06 14:00:19 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

void	read_sphere(t_list **list, t_parser *parser, char *line)
{
	t_shape	*sphere;

	if (*line != 'p')
		return (parsing_error(&parser->errors));
	line++;
	skip_whitespace(&line);
	sphere = malloc(sizeof(*sphere));
	if (sphere == NULL)
		return (parsing_error(&parser->errors));
	sphere->shape = SPHERE;
	line = read_coordinates(line, sphere->position);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_diam_height(line, &sphere->diameter);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_colours(line, sphere->colour);
	if (line == NULL)
		return (free(sphere), parsing_error(&parser->errors));
	ft_lstadd_back(list, ft_lst_new_shape(sphere));
}
