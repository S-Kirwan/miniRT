/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:04:10 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/26 13:02:02 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	add_decimals(char *str, double result)
{
	double	divisor;

	divisor = 10.0;
	while (*str >= '0' && *str <= '9')
	{
		result += (*str - 48) / divisor;
		divisor *= 10;
		str++;
	}
	return (result);
}

double	ft_atof(char *str)
{
	double	result;
	int		sign;

	result = 0.0;
	sign = 1;
	while (*str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	if (*str == '.')
		result = add_decimals(str + 1, result);
	return (result * sign);
}

/*
#include <stdio.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	printf("ft_atof of %s = %f\n", argv[1], ft_atof(argv[1]));
	printf("atof of %s = %f\n", argv[1], atof(argv[1]));
	(void)argc;
}
*/
