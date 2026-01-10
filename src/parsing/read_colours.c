/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_colours.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:18:03 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/23 12:59:32 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parsing.h"

char *read_colours(char *line, int colours[3])
{
	char	*colour_substr;
	int		colour;
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3 && ft_isdigit(line[j]))
			j++;
		if (!valid_char_post_element(i, line[j]))
			return (NULL);
		colour_substr = ft_substr(line, 0, j);
		if (colour_substr == NULL)
			return (NULL);
		colour = ft_atoi(colour_substr);
		if (colour > 255 || colour < 0)
			return (free(colour_substr), NULL);
		free(colour_substr);
		colours[i] = colour;
		line += j + 1;
		i++;
	}
	return (line);
}
