/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 11:59:38 by skirwan           #+#    #+#             */
/*   Updated: 2025/02/10 14:37:59 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int num)
{
	int		digits;
	long	divisor;
	long	ln;
	char	c;

	digits = 0;
	divisor = 1;
	ln = num;
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

int	put_format(char c, va_list valist)
{
	int	chars;

	chars = 0;
	if (c == 'c')
		chars += ft_putchar(va_arg(valist, int));
	if (c == 's')
		chars += ft_putstr(va_arg(valist, char *));
	if (c == 'u')
		chars += ft_putunbr(va_arg(valist, int));
	if (c == 'd' || c == 'i')
		chars += ft_putnbr(va_arg(valist, int));
	if (c == 'p')
		chars += ft_putptr(va_arg(valist, void *), "0123456789abcdef");
	if (c == 'x' || c == 'X')
		chars += ft_puthex(va_arg(valist, int), c, "0123456789abcdef");
	if (c == '%')
	{
		chars++;
		write(1, "\%", 1);
	}
	return (chars);
}

int	run_format(const char *format, va_list valist)
{
	int	chars;

	chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			chars += put_format(*format, valist);
			format++;
			if (!(*format))
				return (chars);
		}
		if (*format != '%')
		{
			write(1, format, 1);
			format++;
			chars++;
		}
	}
	return (chars);
}

int	ft_printf(const char *format, ...)
{
	int		chars;
	va_list	valist;

	va_start(valist, format);
	chars = run_format(format, valist);
	va_end(valist);
	return (chars);
}
