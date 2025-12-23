/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:36:27 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:01:54 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}
/*
void	test(char c)
{
	printf("ft_isalpha for character %c = %i", c, ft_isalpha(c));
	printf("\n");
}

int	main(void)
{
	test('A');
	test('Z');
	test('/');
	test('z');
	test('1');
	test('b');
	test('u');
	test('<');
	test('\n');
	test('@');
	test('9');
	return (0);
}
*/
