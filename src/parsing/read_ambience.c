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

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <unistd.h>

int	read_ambient_ratio(t_ambience *ambience, char *line)
{
	float	ratio;
	int		decimal_points;
	int		i;
	
	decimal_points = 0;
	i = 0;
	while ((ft_isdigit(line[i]) || line[i] == '.') && decimal_points < 1)
	{
		if (line[i] == '.')
			decimal_points++;
		i++;
	}
	if (i < 2 || !ft_isspace(line[i]))
	{
		write(STDERR_FILENO, "Invalid ambient ratio\n", 22);
		return (-1);
	}
	ratio = ft_atof(ft_substr(line, 0, i));
	if (ratio < 0.0 || ratio > 1.0)
		return (-1);
	return (i);
}

void	read_ambience(t_ambience *ambience, t_parser *parser, char *line)
{
	if (parser->ambience != 0)
		(free(line), exit(EXIT_FAILURE)); // Only one ambience element allowed
	while (*line == ' ' || *line == '\t')
		line++;
	if (read_ambient_ratio(ambience, line) < 0)
		parser->errors++;
}
