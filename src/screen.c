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
#include <math.h>

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

void render(t_data *all)
{
    int x, y;
    float t;
    
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            t_vector ray_dir = get_ray_direction(all->camera, x, y);
            if (sphere_hit(all->spheres, all->camera, ray_dir, &t))
                mlx_pixel_put(all->mlx, all->win, x, y, 0xFFFFFF);
                              // rgb_to_hex(all->spheres->red,
                              //            all->spheres->green,
                              //            all->spheres->blue));
            else
                mlx_pixel_put(all->mlx, all->win, x, y, 0x000000);
        }
    }
}

void	scan_screen(t_data *all)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mlx_pixel_put(all->mlx, all->win, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	t_data	all;
	
	init(&all);
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, WIDTH, HEIGHT, "Testing purposes");
	render(&all);
	mlx_loop(all.mlx);
	return (0);

}
