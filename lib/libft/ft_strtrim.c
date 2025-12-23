/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 14:12:38 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:48:56 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	end(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) != NULL && (i > 0))
		i--;
	return (i);
}

size_t	beginning(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (ft_strchr(set, s1[i]) != NULL)
		i++;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	size_t	front;
	size_t	back;
	size_t	i;

	i = 0;
	front = beginning(s1, set);
	back = end(s1, set);
	if (front > back)
		return (ft_strdup(""));
	trimmed = malloc((back - front) + 2);
	if (trimmed == NULL)
		return (NULL);
	while (s1[front] && (front <= back))
		trimmed[i++] = s1[front++];
	trimmed[i] = '\0';
	return (trimmed);
}
/*
void	test(char const *s1, char const *set)
{
	printf("trimmed string '%s' of chars '%s' -->", s1, set);
	printf("'%s'\n", ft_strtrim(s1, set));
	printf("\n");
}

int	main(void)
{
	test("callous", "abcd");
	test("callousabc", "abcd");
	test("runningrun", "unr");
	test("play", "12");
	test("runabcrun", "abc");
	return (0);
}
*/
