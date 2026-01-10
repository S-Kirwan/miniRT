/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambience.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:38:54 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/23 12:56:08 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

void	read_ambience(t_ambience *ambience, t_parser *parser, char *line)
{
	if (parser->ambience != 0)
		return (parsing_error(&parser->errors));
	skip_whitespace(&line);
	line = read_ratio(line, &ambience->ratio);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	skip_whitespace(&line);
	if (read_colours(line, ambience->colour) == NULL)
		return (parsing_error(&parser->errors));
}
