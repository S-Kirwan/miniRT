/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   receive_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:07:39 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 15:37:22 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include "miniRT.h"

int	read_over_spaces(int scene_fd)
{
	ssize_t	bytes_read;
	char	buffer;

	buffer = ' ';
	while (buffer == ' ' || buffer == '\t')
		bytes_read = read(scene_fd, &buffer, 1);
	if (bytes_read < 0)
		return (perror("Error\nread"), READ_ERROR);
	if (!ft_isdigit(buffer))
		return (INVALID_CHARACTER);
	return (buffer);
}

int	read_scene(t_data *data, t_parser *parser)
{
	char	*buffer;

	buffer = get_next_line(parser->scene_fd);
	while (buffer != NULL)
	{
		while (*buffer == ' ' || *buffer == '\t')
			buffer++;
		if (*buffer == 'A')
			read_ambience(data->ambience, parser, buffer + 1);
		else if (*buffer == 'C')
			read_camera(data, parser, buffer);
		else if (*buffer == 'L')
			read_light(data, parser, buffer);
		else if (*buffer == 's')
			read_light(data, parser, buffer);
		else if (*buffer == 'C')
			read_camera(data, parser, buffer);
		else if (*buffer == 'C')
			read_camera(data, parser, buffer);
	}
	return (0);
}

int	receive_scene(t_data *data, int scene_fd)
{
	t_parser	*parser;

	ft_bzero(parser, sizeof(*parser));
	parser->scene_fd = scene_fd;
return (0); }
