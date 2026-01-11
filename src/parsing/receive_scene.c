/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:07:39 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/06 13:51:01 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"

int	read_scene(t_data *data, t_parser *parser)
{
	char	*buffer;
	char	*line;
	int		temp;

	temp = 2;
	buffer = get_next_line(parser->scene_fd);
	while (buffer != NULL)
	{
		line = buffer;
		skip_whitespace(&line);
		if (*line == 'A')
			read_ambience(data->ambience, parser, line + 1);
		else if (*line == 'C')
			read_camera(data->camera, parser, line + 1);
		else if (*line == 'L')
			read_light(data->light, parser, line + 1);
		else if (*line == 's')
			read_sphere(&data->shape_list, parser, line + 1);
		else if (*line == 'p')
			read_plane(&data->shape_list, parser, line + 1);
		else if (*line == 'c')
			read_cylinder(&data->shape_list, parser, line + 1);
		else if (*line == '\n')
			temp++;
		else
		{
			printf("Error\n");
			exit(1); // cleanup required
		}
		free(buffer);
		if (parser->errors > 0)
		{
			printf("Error\n");
			exit(1); // cleanup required
		}
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
