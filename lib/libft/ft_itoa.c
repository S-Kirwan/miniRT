/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 16:35:50 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 19:46:56 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include <stdio.h>

int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n < 0)
	{
		digits++;
	}
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	int		digits;
	char	*str;
	long	nbr;

	nbr = (long)n;
	digits = count_digits(nbr);
	str = ft_calloc((digits + 1), 1);
	if (!(str))
		return (NULL);
	str[digits] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
	}
	while (digits--)
	{
		if (str[digits] == '-')
			break ;
		str[digits] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (str);
}
/*
void	test(int n)
{
	printf("converting int '%d' to ascii using ft_itoa = ", n);
	printf("'%s'\n", ft_itoa(n));
}

int	main(void)
{
	test(-901);
	test(3429);
	test(5);
	test(-2147483647);
	test(2147483647);
	test(247);
	test(-0);
}
*/
