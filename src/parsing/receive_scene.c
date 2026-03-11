/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:07:39 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/07 22:39:21 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"
#include "window_management.h"

void	p_clean(t_data *data, char *line, int fd)
{
	char	*buffer;
	char	*line_2;

	write(2, "Error\n", 6);
	free(line);
	buffer = get_next_line(fd);
	while (buffer)
	{
		line_2 = buffer;
		free (line_2);
		buffer = get_next_line(fd);
	}
	free(data->ambience);
	free(data->camera);
	free(data->light);
	free(data->mlx_data->mlx_img);
	free(data->mlx_data);
	free(data);
	close(fd);
}

void	read_scene(t_data *data, t_parser *parser)
{
	char	*buffer;
	char	*line;

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
		else if (*line != '\n' || parser->errors > 0)
			(p_clean(data, line, parser->scene_fd), exit(0));
		free(buffer);
		buffer = get_next_line(parser->scene_fd);
	}
}

int	validate_scene(t_data *data, t_parser parser)
{
	if (parser.light != 1)
	{
		free_shape_list(data);
		(p_clean(data, NULL, parser.scene_fd), exit(0));
	}
	if (parser.camera != 1)
	{
		free_shape_list(data);
		(p_clean(data, NULL, parser.scene_fd), exit(0));
	}
	if (parser.ambience != 1)
	{
		free_shape_list(data);
		(p_clean(data, NULL, parser.scene_fd), exit(0));
	}
	return (0);
}

int	receive_scene(t_data *data, int scene_fd)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	parser.scene_fd = scene_fd;
	read_scene(data, &parser);
	close(scene_fd);
	return (validate_scene(data, parser));
}
