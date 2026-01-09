/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:40:37 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/23 14:48:05 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <stdio.h>

// Magic number 2 is passed to valid char check, as in other cases when i = 2
// it is the end of the element. This is the same as after one reading of FOV.
// Potentially could enum this
char	*read_fov(char *line, int *fov_ref)
{
	char	*fov_substr;
	int		fov;
	int		i;

	i = 0;
	while (ft_isdigit(line[i]))
		i++;
	if (!valid_char_post_element(2, line[i]))
		return (NULL);
	fov_substr = ft_substr(line, 0, i);
	fov = ft_atoi(fov_substr);
	if (fov < 0 || fov > 180)
		return (free(fov_substr), NULL);
	free(fov_substr);
	*fov_ref = fov;
	return (line);
}

void	read_camera(t_camera *camera, t_parser *parser, char *line)
{
	if (parser->camera != 0)
		return (parsing_error(&parser->errors));
	while (ft_isspace(*line))
		line++;
	line = read_coordinates(line, camera->position);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	while (ft_isspace(*line))
		line++;
	line = read_vectors(line, camera->orientation);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	while (ft_isspace(*line))
		line++;
	line = read_fov(line, &camera->fov);
	if (line == NULL)
		return (parsing_error(&parser->errors));
	return ;
}
