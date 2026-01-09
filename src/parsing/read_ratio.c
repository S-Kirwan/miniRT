/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_ratio.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 11:33:45 by skirwan           #+#    #+#             */
/*   Updated: 2025/12/23 11:38:22 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*read_ratio(char *line, float *ratio_ref)
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
		return (NULL);
	ratio_substr = ft_substr(line, 0, i);
	ratio = ft_atof(ratio_substr);
	free(ratio_substr);
	if (ratio < 0.0 || ratio > 1.0)
		return (NULL);
	*ratio_ref = ratio;
	return (line + i);
}
