/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:13:20 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:02:08 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
/*
void	test (char c)
{
	printf("ft_isascii for char %c = %d \n", c, ft_isascii(c));
}

int	main(void)
{
	test('8');
	test(100);
	test('a');
	test('u');
	test(-5);
	test(10);
}
*/
