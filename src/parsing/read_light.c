/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:54:52 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 15:16:13 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

void	read_light(t_light *light, t_parser *parser, char *line)
{
	if (parser->light != 0)
		return (parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_coordinates(line, light->position);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_ratio(line, &light->brightness);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	skip_whitespace(&line);
	if (*line == '\0')
		return ;
	line = read_colours(line, light->colour);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	return ;
}
