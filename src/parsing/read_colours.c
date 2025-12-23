/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:18:03 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/15 12:02:24 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"
#include <stdio.h>

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

int	is_valid_char_post_colour(int i, char c)
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

int	read_colours(char *line, int colours[3])
{
	char	*colour_substr;
	int		colour;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			if (!ft_isdigit(line[j]))
				return (-1);
			j++;
		}
		if (!is_valid_char_post_colour(i, line[j]))
			return (-1);
		colour_substr = ft_substr(line, 0, 3);
		if (colour_substr == NULL)
			return (free(colour_substr), -1);
		colour = ft_atoi(colour_substr);
		if (colour > 255 || colour < 0)
			return (free(colour_substr), -1);
		free(colour_substr);
		colours[i] = colour;
		line += j + 1;
		i++;
	}
	return (0);
}
