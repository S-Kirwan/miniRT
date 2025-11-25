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

int	read_scene(t_data *data, t_parser *parser, int scene_fd)
{
	char	*buffer;

	while (read(scene_fd, buffer, 1) > 0)
	{
		if (*buffer == ' ' || *buffer == '\n')
			continue;
		else if (*buffer == 'A')
			read_ambience(data, parser, scene_fd);
		else if (*buffer == 'C')
			read_camera(data, parser, scene_fd);
		else if (*buffer == 'L')
			read_light(data, parser, scene_fd);
		else if (*buffer == 'p')
			read_plane;
		else if (*buffer == 's')
			read_sphere;
		else if (*buffer == 'c')
			read_cylinder;
		else
			return (-1); // requires exit function to free mallocs in data struct
	}
	return (0);
}

int	receive_scene(t_data *data, int scene_fd)
{
	t_parser	*parser;

	ft_bzero(parser, sizeof(*parser));

	return (0);
}
