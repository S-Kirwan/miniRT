/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 10:31:52 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:47:42 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (len && big[i])
	{
		j = 0;
		while ((big[i + j] == little[j]) && big[i + j] && (len >= (i + j)))
			j++;
		if (little[j] == '\0' && (len >= (i + j)))
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
