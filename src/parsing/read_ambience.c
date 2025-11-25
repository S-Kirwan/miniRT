/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambience.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:38:54 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 17:49:01 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"
#include <stdlib.h>

void	read_ambience(t_data *data, t_parser *parser, int scene_fd)
{
	t_light	*light;

	if (parser->ambience != 0)
		exit(EXIT_FAILURE); // Only one ambience element allowed + full cleanup required
	light = malloc(sizeof(*light));
	if (light == NULL)
		exit(EXIT_FAILURE); // full cleanup required

}
