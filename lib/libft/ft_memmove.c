/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 14:06:22 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:43:17 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*sdest;
	char	*ssrc;

	sdest = (char *)dest;
	ssrc = (char *)src;
	if (dest < src)
	{
		while (n--)
			*sdest++ = *ssrc++;
	}
	else if (dest > src)
	{
		sdest = sdest + (n - 1);
		ssrc = ssrc + (n - 1);
		while (n--)
			*sdest-- = *ssrc--;
	}
	if (!dest && !src)
		return (0);
	return (dest);
}
