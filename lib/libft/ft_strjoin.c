/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:44:59 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:44:45 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (str == NULL)
		return (0);
	while (*s1)
	{
		*str++ = *s1++;
		i++;
	}
	while (*s2)
	{
		*str++ = *s2++;
		i++;
	}
	*str = '\0';
	return (str - i);
}
/*
void	test(char const *s1, char const *s2)
{
	printf("ft_strjoin of '%s' and '%s' --> ", s1, s2);
	printf("'%s'\n", ft_strjoin(s1, s2));
}

int	main(void)
{
	test("Hello", "World");
	return (0);
}
*/
