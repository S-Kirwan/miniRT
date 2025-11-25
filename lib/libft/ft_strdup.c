/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:34:32 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:06:39 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	dest = (char *)malloc(ft_strlen(s) + 1);
	if (dest == NULL)
		return (NULL);
	while (*s)
	{
		dest[i] = *s++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
