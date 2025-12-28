/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_vectors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 14:46:22 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/24 15:49:11 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	read_vector(char *line, float *vector_ref)
{
	float	vector;
	char	*vector_substr;
	int		decimal_points;
	int		sign;
	int		i;
	
	decimal_points = 0;
	i = 0;
	sign = 1;
	if (line[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(line[i]) || line[i] == '.')
	{
		if (line[i] == '.')
			decimal_points++;
		i++;
	}
	vector_substr = ft_substr(line, 0, i);
	vector = ft_atof(vector_substr) * sign;
	free(vector_substr);
	if (vector < -1.0 || vector > 1.0)
		return (-1);
	*vector_ref = vector;
	return (i);
}

char	*read_vectors(char *line, float vectors[3])
{
	int		bytes_read;
	int		i;

	i = 0;
	while (i < 3)
	{
		bytes_read = read_vector(line, &vectors[i]);
		if (bytes_read <= 0)
			return (NULL);
		line += bytes_read;
		if (!valid_char_post_element(i, *line))
			return (NULL);
		line++;
		i++;
	}
	return (line);
}
