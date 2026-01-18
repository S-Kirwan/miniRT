/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_initialisation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 15:50:02 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 16:16:35 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"

int		calculate_img_offset(int line_length, int bpp, int x, int y)
{
	int	offset;

	offset = (y * line_length) + (x * (bpp / 8));
	return (offset);
}

void	place_pixel_to_img(t_mlx_img *mlx_img, int x, int y, int colour)
{
	char	*pixel;

	pixel = mlx_img->addr + calculate_img_offset(mlx_img->line_length, mlx_img->bpp, x, y);
	*(unsigned int *)pixel = colour;
}

void	create_mlx_img(t_mlx_img *mlx_img, void *mlx_instance)
{
	mlx_img->image = mlx_new_image(mlx_instance, WIDTH, HEIGHT);
	mlx_img->addr = mlx_get_data_addr(mlx_img->image, &mlx_img->bpp,
		&mlx_img->line_length, &mlx_img->endian);
}
