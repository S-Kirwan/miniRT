/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ambience.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:38:54 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/15 14:28:56 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <stdio.h>

int	read_ambient_ratio(t_ambience *ambience, char *line)
{
	float	ratio;
	char	*ratio_substr;
	int		decimal_points;
	int		i;
	
	decimal_points = 0;
	i = 0;
	while (ft_isdigit(line[i]) || line[i] == '.')
	{
		if (line[i] == '.')
			decimal_points++;
		i++;
	}
	if (!ft_isspace(line[i]) || decimal_points > 1)
		return (-1);
	ratio_substr = ft_substr(line, 0, i);
	ratio = ft_atof(ratio_substr);
	free(ratio_substr);
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);
	ambience->ratio = ratio;
	return (i);
}

void	read_ambience(t_ambience *ambience, t_parser *parser, char *line)
{
	int	bytes_read;

	if (parser->ambience != 0)
	{
		printf("Only one ambience allowed\n");
		(free(line), exit(EXIT_FAILURE)); // Only one ambience element allowed
	}
	while (ft_isspace(*line))
		line++;
	printf("*line = %c\n", *line);
	bytes_read = read_ambient_ratio(ambience, line);
	if (bytes_read < 0)
	{
		printf("ratio error\n");
		parser->errors++;
		return ;
	}
	printf("ratio = %f\n", ambience->ratio);
	line += bytes_read;
	while (ft_isspace(*line))
		line++;
	if (read_colours(line, ambience->colour) < 0)
	{
		printf("colours error\n");
		parser->errors++;
		return ;
	}
	print_colours_test(ambience->colour);
}
