/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 12:54:25 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 18:41:50 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (start > ft_strlen(s))
	{
		sub = malloc(1);
		if (!(sub))
			return (NULL);
		ft_bzero(sub, 1);
		return (sub);
	}
	i = 0;
	while (s[start + i])
		i++;
	if (len > i)
		len = i;
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (s[start] && len--)
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}
