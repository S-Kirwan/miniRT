/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:01:10 by skirwan           #+#    #+#             */
/*   Updated: 2025/05/01 15:02:32 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *nptr)
{
	long	num;
	long	sign;

	sign = 1;
	num = 0;
	while ((*nptr == ' ') || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if ((*nptr > 'A' && *nptr < 'Z') || (*nptr > 'a' && *nptr < 'z'))
		return (0);
	if (*nptr == '-')
		sign = -1;
	if (*nptr == '+' || *nptr == '-')
		nptr++;
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = (num * 10) + (*nptr - '0');
		nptr++;
	}
	return (num * sign);
}
