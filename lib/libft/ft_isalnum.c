/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:58:55 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:01:39 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
/*
void	test(char c)
{
	printf("ft_isalnum for character %c = %d", c, ft_isalnum(c));
	printf("\n");
}

int	main(void)
{
	test('A');
	test('B');
	test('1');
	test('0');
	test('9');
	test('@');
	test('*');
	test('^');
	test('<');
	test('F');
	test('Z');
	test('a');
	test('b');
	test('z');
	return (0);
}
*/
