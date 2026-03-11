/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:54:52 by skirwan           #+#    #+#             */
/*   Updated: 2026/02/08 15:35:29 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

void	read_light(t_light *light, t_parser *parser, char *line)
{
	skip_whitespace(&line);
	line = read_coordinates(line, light->position);
	if (line == NULL)
		return (parsing_error(&parser->errors, "light coordinates"));
	skip_whitespace(&line);
	line = read_ratio(line, &light->brightness);
	if (line == NULL)
		return (parsing_error(&parser->errors, "light ratio"));
	skip_whitespace(&line);
	if (*line == '\0')
		return ;
	line = read_colours(line, light->colour);
	if (line == NULL)
		return (parsing_error(&parser->errors, "light colours"));
	parser->light++;
}
