/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 17:21:26 by skirwan           #+#    #+#             */
/*   Updated: 2024/12/15 12:04:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write (fd, &c, 1);
}
/*
int	main(void)
{
	ft_putchar_fd('B', 1);
	ft_putchar_fd('a', 1);
	ft_putchar_fd('l', 1);
	ft_putchar_fd('l', 1);
	ft_putchar_fd('s', 1);
	ft_putchar_fd('y', 1);
	return (0);
}
*/
