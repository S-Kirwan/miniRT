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
	all->camera->x_orientation = 5.0;
	all->camera->y_orientation = 0.0;
	all->camera->z_orientation = 0.999;
	all->camera->fov = 90;
	all->camera->normal.x = all->camera->x_orientation;
	all->camera->normal.y = all->camera->y_orientation;
	all->camera->normal.z = all->camera->z_orientation;
	all->camera->fov_rad = all->camera->fov * M_PI / 180.0;
	all->camera->aspect = (float)WIDTH / (float)HEIGHT;
	all->camera->viewport_h = 2.0 * tan(all->camera->fov_rad / 2.0);
	all->camera->viewport_w = all->camera->viewport_h * all->camera->aspect;
	normalize(&all->camera->normal);
}

int	sphere_hit(t_sphere *sphere, t_vector ray_origin, t_vector ray_dir, float *t)
{
	t_vector	oc = {ray_origin.x - sphere->x, ray_origin.y - sphere->y, ray_origin.z - sphere->z};
	float		a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	float		b = 2.0f * (oc.x * ray_dir.x + oc.y * ray_dir.y + oc.z * ray_dir.z);
	float		c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (sphere->diameter / 2.0f) * (sphere->diameter / 2.0f); 
	float		discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return (0); 
	}
	float	t0 = (-b - sqrt(discriminant)) / (2.0f * a);
	float	t1 = (-b + sqrt(discriminant)) / (2.0f * a);

	if (t0 > 0)
		*t = t0;
	else if (t1 > 0)
			*t = t1;
	else
		return (0);
	return (1);
}

//Formula for raytracing is P(t) = O + tD
//O is the camera position (x,y,z)
//D is the orientation vector + pixel offset from camera orientation vector
//t is the distance of the ray
void	raytracing(t_data *all)
{
	t_vector	ray_origin = {all->camera->x, all->camera->y, all->camera->z};
	int		x;
	int		y;
	float	u;
	float	v;
	float	t;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((x + 0.5f) / WIDTH - 0.5f) * all->camera->viewport_w;
			v = (0.5f - (y + 0.5f) / HEIGHT) * all->camera->viewport_h;
			t_vector	ray_dir = {all->camera->normal.x + u, all->camera->normal.y + v, all->camera->normal.z};
			normalize(&ray_dir);
             if (sphere_hit(all->spheres, ray_origin, ray_dir, &t))
                 mlx_pixel_put(all->mlx, all->win, x, y, 0xFFFFFF);
                               // rgb_to_hex(all->spheres->red,
                               //            all->spheres->green,
                               //            all->spheres->blue));
             else
                 mlx_pixel_put(all->mlx, all->win, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

//Normalizes a vector which has to have x y and z values already. It modifies it 
//dirrectly, so a pointer is needed. And is better to have a t_vector type in the
//struct to be able to access the original info if needed
void	normalize(t_vector	*v)
{
	float		len;

	len = sqrt((v->x * v->x) + (v->y * v->y) + (v->z * v->z));
	if (len == 0)
		return ;
	v->x /= len;
	v->y /= len;
	v->z /= len;
}

int	main(void)
{
	t_data	all;
	
	init(&all);
	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, WIDTH, HEIGHT, "Testing purposes");
	raytracing(&all);
	mlx_loop(all.mlx);
	return (0);

}
