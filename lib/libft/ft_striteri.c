/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:01:50 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:06:52 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	i;

	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}
/*
void	print_c(unsigned int i, char *str)
{
	printf("** '%s' ", str);
	printf("'%d' ** \n", i);
}

int	main(void)
{
	ft_striteri("012345", print_c);
	return (0);
}
*/
