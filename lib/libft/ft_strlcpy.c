/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 15:08:15 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 15:32:23 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	while ((size > 1) && (src[i] != '\0'))
	{
		dst[i] = src[i];
		i++;
		size--;
	}
	if (size >= 1)
		dst[i] = '\0';
	return (ft_strlen(src));
}
/*
int	main(void)
{
	char	*dst = "Hello World";
	char	*src = "Computers1234567";
	size_t	size = 12;

	printf("Dest string = '%s'\nSrc string = '%s'\n", dst, src);
	ft_strlcpy(dst, src, size);
	printf("Dest string after ft_strlcpy = '%s'\n", dst);
	return (0);
}
*/
