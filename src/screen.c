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
#include "../includes/miniRT.h"
#include "../includes/parsing.h"

#define WIDTH 500
#define HEIGHT 500

void	init(t_data *all)
{
	//TODO: Sphere
	all->spheres = malloc(sizeof(t_sphere));
	all->spheres->x = 20;
	all->spheres->y = 50;
	all->spheres->z = 100;
	all->spheres->diameter = 7.5;
	all->spheres->red = 163;
	all->spheres->green = 234;
	all->spheres->blue = 42;

	//TODO: Camera
	all->camera = malloc(sizeof(t_camera));
	all->camera->x = -50;
	all->camera->y = 0;
	all->camera->z = 20;
	all->camera->x_orientation = 0.0;
	all->camera->y_orientation = 0.0;
	all->camera->z_orientation = 1.0;
	all->camera->fov = 90;
}

int	main(void)
{
	t_data	all;
	void	*mlx;
	void	*win;
	
	init(&all);
	mlx = mlx_init();
	win = mlx_new_window(mlx, WIDTH, HEIGHT, "Testing purposes");
	mlx_pixel_put(mlx, win, WIDTH / 2, HEIGHT / 2, 0xFFFFFF);
	mlx_loop(mlx);
	return (0);

}
