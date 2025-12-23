/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:27:27 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:11:45 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
void	test(char c)
{
	printf("ft_toupper changes char %c to char %c", c, ft_toupper(c));
	printf("\n");
}

int	main(void)
{
	test('a');
	test('z');
	test('b');
	test('u');
	test('v');
	test('8');
	test('M');
	test('Z');
	test('A');
	test('/');
	return (0);
}
*/
