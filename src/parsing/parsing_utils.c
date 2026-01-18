/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 12:46:09 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 17:53:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"
#include <stdio.h>

void	parsing_error(int *errors)
{
	*errors += 1;
	return ;
}

t_list	*ft_lst_new_shape(t_shape *shape)
{
	t_list	*new_node;

	new_node = malloc(sizeof(*new_node));
	if (new_node == NULL)
		return (NULL);
	new_node->shape = shape;
	new_node->next = NULL;
	return (new_node);
}

void	skip_whitespace(char **line)
{
	char	*line_ptr;

	line_ptr = *line;
	while (ft_isspace(*line_ptr))
		line_ptr++;
	*line = line_ptr;
}

char	*read_diam_height(char *line, float *ref)
{
	char	*measurement_substr;
	int		decimal_places;
	int		i;

	i = 0;
	decimal_places = 0;
	while (ft_isdigit(line[i]) || line[i] == '.')
	{
		if (line[i] == '.')
			decimal_places++;
		i++;
	}
	if (!ft_isspace(line[i]) || decimal_places > 1)
		return (NULL);
	measurement_substr = ft_substr(line, 0, i);
	if (measurement_substr == NULL)
		return (NULL);
	*ref= ft_atof(measurement_substr);
	free(measurement_substr);
	if (*ref <= 0.0)
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
