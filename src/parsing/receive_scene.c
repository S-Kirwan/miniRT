/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:07:39 by skirwan           #+#    #+#             */
/*   Updated: 2026/02/08 15:41:35 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"

void	parsing_error_cleanup(t_data *data, char *line)
{
	perror("Error\n");
	free(line);
	free(data->ambience);
	free(data->camera);
	free(data->light);
	free(data->mlx_data->mlx_img);
	free(data->mlx_data);
	free(data);
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
			(parsing_error_cleanup(data, line), exit(0));
		free(buffer);
		buffer = get_next_line(parser->scene_fd);
	}
}

int	validate_scene(t_parser parser)
{
	if (parser.light != 1)
		return (-1);
	if (parser.camera != 1)
		return (-1);
	if (parser.ambience != 1)
		return (-1);
	return (0);
}

int	receive_scene(t_data *data, int scene_fd)
{
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	parser.scene_fd = scene_fd;
	read_scene(data, &parser);
	return (validate_scene(parser));
}
