/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:20:30 by skirwan           #+#    #+#             */
/*   Updated: 2025/02/09 17:00:33 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr(void *ptr, char *hex)
{
	unsigned long	address;
	int				digits;
	int				i;
	char			buf[16];

	if (ptr == 0)
	{
		write (1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	address = (unsigned long)ptr;
	digits = 2;
	i = 0;
	while (address)
	{
		buf[i] = hex[address % 16];
		address /= 16;
		digits++;
		i++;
	}
	while (--i >= 0)
		write(1, &buf[i], 1);
	return (digits);
}

int	ft_puthex(unsigned int num, char fm, char *hex)
{
	int		digits;
	long	divisor;
	char	c;

	divisor = 1;
	digits = 0;
	while (divisor * 16 <= num)
		divisor *= 16;
	while (divisor)
	{
		c = hex[num / divisor];
		if (fm == 'X' && c > '9')
			c -= 32;
		write(1, &c, 1);
		num = num % divisor;
		divisor /= 16;
		digits++;
	}
	return (digits);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!(str))
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_putchar(unsigned char c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putnbr(int num)
{
	long	divisor;
	long	ln;
	int		digits;
	char	c;

	ln = num;
	digits = 0;
	divisor = 1;
	if (ln < 0)
	{
		write(1, "-", 1);
		ln *= -1;
		digits++;
	}
	while (divisor * 10 <= ln)
		divisor *= 10;
	while (divisor)
	{
		c = ln / divisor + '0';
		write(1, &c, 1);
		ln = ln % divisor;
		divisor /= 10;
		digits++;
	}
	return (digits);
}
