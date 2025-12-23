/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 18:34:56 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/19 11:35:46 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*copy_string(int len, const char *s)
{
	char	*str;
	int		i;

	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len && *s)
	{
		str[i] = s[i];
		i++;
	}
	str[len] = '\0';
	return (str);
}

int	array_size(char const *s, char c)
{
	int	strings;
	int	parse;

	strings = 0;
	while (*s)
	{
		parse = 0;
		while ((*s == c) && *s)
			s++;
		while (*s != c && *s)
		{
			if (parse == 0)
			{
				strings++;
				parse = 1;
			}
			s++;
		}
	}
	return (strings);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		ii;
	char	**split_array;

	ii = 0;
	split_array = malloc((array_size(s, c) + 1) * sizeof(*split_array));
	if (!split_array)
		return (NULL);
	while (*s)
	{
		i = 0;
		while (*s == c && *s)
			s++;
		while (s[i] != c && s[i])
			i++;
		if (i > 0)
		{
			split_array[ii] = copy_string(i, s);
			s += ft_strlen(split_array[ii]);
			ii++;
		}
	}
	split_array[ii] = NULL;
	return (split_array);
}
