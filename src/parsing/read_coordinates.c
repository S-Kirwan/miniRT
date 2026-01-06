/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_coordinates.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:41:49 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/27 15:57:34 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

char	*read_coordinates(char *line, float coordinates[3])
{
	float	coordinate;
	char	*coord_substr;
	int		decimal_places;
	int		sign;
	int		i;
	int		j;
	
	i = 0;
	while (i < 3)
	{
		sign = 1;
		j = 0;
		decimal_places = 0;
		if (line[j] == '-')
		{
			sign = -1;
			line++;
		}
		while (ft_isdigit(line[j]) || (line[j] == '.' && decimal_places < 1))
		{
			if (line[j] == '.')
				decimal_places++;
			j++;
		}
		if (!valid_char_post_element(i, line[j]))
			return (NULL);
		coord_substr = ft_substr(line, 0, j);
		if (coord_substr == NULL)
			return (NULL);
		coordinate = ft_atof(coord_substr);
		free(coord_substr);
		coordinates[i] = coordinate * sign;
		line += j + 1;
		i++;
	}
	return (line);
}
