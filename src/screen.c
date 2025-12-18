/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 19:53:41 by aramos            #+#    #+#             */
/*   Updated: 2025/12/11 19:53:57 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	screen(void)
{
	void	*mlx = mlx = mlx_init();
	void	*win = mlx_new_window(mlx, 500, 500, "Testing purposes");
	printf ("%p", win);
	mlx_loop(mlx);
	return (1);
}
