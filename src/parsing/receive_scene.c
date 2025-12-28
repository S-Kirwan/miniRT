/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:07:39 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/27 15:51:12 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"
#include <stdio.h>

int	read_scene(t_data *data, t_parser *parser)
{
	char	*buffer;

	buffer = get_next_line(parser->scene_fd);
	while (buffer != NULL)
	{
		while (ft_isspace(*buffer))
			buffer++;
		if (*buffer == 'A')
			read_ambience(data->ambience, parser, buffer + 1);
		else if (*buffer == 'C')
			read_camera(data->camera, parser, buffer + 1);
		else if (*buffer == 'L')
			read_light(data->light, parser, buffer + 1);
		else if (*buffer == 's')
			read_sphere(data->shapes, parser, buffer + 1);
		// else if (*buffer == 'C')
		// 	read_camera(data, parser, buffer);
		// else if (*buffer == 'C')
		// 	read_camera(data, parser, buffer);
		else
			exit(1); // cleanup required
		free(buffer);
		buffer = get_next_line(parser->scene_fd);
	}
	return (0);
}

int	receive_scene(t_data *data, int scene_fd)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	parser.scene_fd = scene_fd;
	read_scene(data, &parser);
	return (0); 
}
