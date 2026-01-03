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

void put_point(t_data *all, int x, int y, int color)
{
    int size = 3; // small 3x3 square
    for (int i = -size; i <= size; i++)
        for (int j = -size; j <= size; j++)
            mlx_pixel_put(all->mlx, all->win, x + i, y + j, color);
}

t_vector project(t_data *all, t_vector p)
{
    float scale = 200.0f;
    float dz = p.z - all->camera->z;
    if (dz <= 0.01f) dz = 0.01f; // avoid division by 0
    t_vector proj;
    proj.x = (p.x - all->camera->x) * scale / dz + WIDTH / 2;
    proj.y = (p.y - all->camera->y) * scale / dz + HEIGHT / 2;
    return proj;
}


void draw_line(t_data *all, t_vector from, t_vector to, int color)
{
    int steps = 100;
    float dx = (to.x - from.x) / steps;
    float dy = (to.y - from.y) / steps;
    for (int i = 0; i <= steps; i++)
        mlx_pixel_put(all->mlx, all->win, from.x + dx*i, from.y + dy*i, color);
}

void	init(t_data *all)
{
	//TODO: Lights
	all->lights = malloc(sizeof(t_light));
	all->lights->x = 0;
	all->lights->y = 0;
	all->lights->z = 0;

	//TODO: Sphere
	all->spheres = malloc(sizeof(t_sphere));
	all->spheres->x = -50;
	all->spheres->y = 0;
	all->spheres->z = 100;
	all->spheres->diameter = 50;
	all->spheres->red = 163;
	all->spheres->green = 234;
	all->spheres->blue = 42;

	//TODO: Camera
	all->camera = malloc(sizeof(t_camera));
	all->camera->x = -50;
	all->camera->y = 0;
	all->camera->z = 20;
	all->camera->x_orientation = 0;
	all->camera->y_orientation = 0;
	all->camera->z_orientation = 1;
	all->camera->fov = 90;
	all->camera->normal.x = all->camera->x_orientation;
	all->camera->normal.y = all->camera->y_orientation;
	all->camera->normal.z = all->camera->z_orientation;
	all->camera->fov_rad = all->camera->fov * M_PI / 180.0;
	all->camera->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	all->camera->viewport_h = 2.0 * tan(all->camera->fov_rad / 2.0);
	all->camera->viewport_w = all->camera->viewport_h * all->camera->aspect_ratio;
	normalize(&all->camera->normal);
}

//oc is the distance between the origin ray (camera vector) and the center of the sphere
//that means that oc is equal to (O - C)
int	sphere_hit(t_sphere *sphere, t_vector ray_origin, t_vector ray_dir, float *t)
{
	t_vector	oc = {ray_origin.x - sphere->x, ray_origin.y - sphere->y, ray_origin.z - sphere->z};
	float		a = ray_dir.x * ray_dir.x + ray_dir.y * ray_dir.y + ray_dir.z * ray_dir.z;
	float		b = 2.0f * (oc.x * ray_dir.x + oc.y * ray_dir.y + oc.z * ray_dir.z);
	float		c = oc.x * oc.x + oc.y * oc.y + oc.z * oc.z - (sphere->diameter / 2.0f) * (sphere->diameter / 2.0f); 
	float		discriminant = b * b - 4 * a * c;
	float		t0;
	float		t1;

	if (discriminant < 0)
	{
		return (0); 
	}
	t0 = (-b - sqrt(discriminant)) / (2.0f * a);
	t1 = (-b + sqrt(discriminant)) / (2.0f * a);
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
//ray_origin = O
//ray_dir = D
// t = t haha
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
			{
				t_vector	hit_point = {ray_origin.x + t * ray_dir.x, ray_origin.y + t * ray_dir.y, ray_origin.z + t * ray_dir.z};
				t_vector	surface_normal = {hit_point.x - all->spheres->x, hit_point.y - all->spheres->y, hit_point.z - all->spheres->z};
				normalize(&surface_normal);
				t_vector	light_dir = {all->lights->x - hit_point.x, all->lights->y - hit_point.y, all->lights->z - hit_point.z};
				normalize(&light_dir);
				float	intensity = surface_normal.x * light_dir.x + surface_normal.y * light_dir.y + surface_normal.z * light_dir.z;
				if (intensity < 0)
					intensity = 0;
				int	r = (int)(all->spheres->red * intensity);
				int	g = (int)(all->spheres->green * intensity);
				int	b = (int)(all->spheres->blue * intensity);
				int	color = (r << 16) | (g << 8) | b;
                mlx_pixel_put(all->mlx, all->win, x, y, color);
				t_vector light_pos = {all->lights->x, all->lights->y, all->lights->z};

				t_vector cam2D   = project(all, (t_vector){all->camera->x, all->camera->y, all->camera->z});
				t_vector light2D = project(all, light_pos);
				// t_vector hit2D   = project(all, hit_point);

				// draw points
				put_point(all, cam2D.x, cam2D.y, 0xFF0000);     // camera = red
				put_point(all, light2D.x, light2D.y, 0xFFFF00); // light = yellow

				// draw ray from camera to hit
				// draw_line(all, cam2D, hit2D, 0x00FF00);         // ray = green
				//
				// // draw ray from hit to light
				// draw_line(all, hit2D, light2D, 0x0000FF);       // light ray = blue
            }
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
