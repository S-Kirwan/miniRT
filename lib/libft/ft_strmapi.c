/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 15:50:16 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:08:53 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str_out;
	int		i;

	i = 0;
	str_out = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!(str_out))
		return (NULL);
	while (s[i])
	{
		str_out[i] = f(i, s[i]);
		i++;
	}
	str_out[i] = '\0';
	return (str_out);
}
/*
char	plus_index(unsigned int n, char c)
{
	c += n;
	return (c);
}
int	main(void)
{
	printf("Applying function plus_index using ft_strmapi to '%s'\n", "0000000");
	printf("= '%s'", ft_strmapi("0000000", plus_index));
	return (0);
}
*/
