/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:49:59 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:02:22 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
void	test(char c)
{
	printf("ft_isdigit for character %c = %d", c, ft_isdigit(c));
	printf("\n");
}

int	main(void)
{
	test('1');
	test('9');
	test('A');
	test('0');
	test('m');
	test('/');
	test('\n');
	test('R');
	test('v');
	test('5');
	return (0);
}
*/
