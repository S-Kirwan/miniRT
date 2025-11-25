/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:15:35 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:50:03 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = ft_strlen(s);
	if (c == '\0')
		return ((char *)(s + len));
	while (len)
	{
		if (s[len - 1] == (char)c)
			return ((char *)(s + (len - 1)));
		len--;
	}
	return (NULL);
}
