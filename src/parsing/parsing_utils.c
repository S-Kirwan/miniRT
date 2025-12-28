/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:46:09 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/27 16:03:28 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdlib.h>

void	parsing_error(int *errors)
{
	errors++;
}

void	print_colours_test(int colours[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Colour %d = %d\n", i, colours[i]);
		i++;
	}
}

void	print_coords_test(float coords[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Coord %d = %f\n", i, coords[i]);
		i++;
	}
}

void	print_vectors_test(float vectors[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Vector %d = %f\n", i, vectors[i]);
		i++;
	}
}

char	*read_diameter(char *line, float *diameter)
{
	char	*diam_substr;
	int		decimal_places;
	int		i;

	i = 0;
	decimal_places = 0;
	while (ft_isdigit(line[i] || line[i] == '.'))
	{
		if (line[i] == '.')
			decimal_places++;
		i++;
	}
	if (!ft_isspace(line[i]) || decimal_places > 1)
		return (NULL);
	diam_substr = ft_substr(line, 0, i);
	if (diam_substr == NULL)
		return (NULL);
	*diameter = ft_atof(diam_substr);
	free(diam_substr);
	if (*diameter <= 0.0)
		return (NULL);
	return (line + i);
}

int	valid_char_post_element(int i, char c)
{
	if (i < 2)
	{
		if (c == ',')
			return (1);
	}
	else if (i == 2)
	{
		if (ft_isspace(c))
			return (1);
		if (c == '\0')
			return (1);
		if (c == '\n')
			return (1);
		if (c == EOF)
			return (1);
	}
	return (0);
}
