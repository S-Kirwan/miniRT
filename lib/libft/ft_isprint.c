/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 17:01:40 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 14:47:50 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (c >= 32 && c < 127)
		return (1);
	return (0);
}
/*
void	test(int c)
{
	printf("ft_isprint for character %c = %d \n", c, ft_isprint(c));
}

int	main(void)
{
	test(' ');
	test(10);
	test(30);
	test(5);
	test(100);
	test(-100);
	test(-5);
	return (0);
}
*/
