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

#include "../inc/miniRT.h"
#include "../inc/parsing.h"
#include "../inc/raytracing.h"

#define WIDTH 500
#define HEIGHT 500

//oc is the distance between the origin ray (camera vector) and the center of the sphere
//that means that oc is equal to (O - C)
int	sphere_hit(t_shape *sphere, t_vector ray_origin, t_vector ray_dir, float *t)
{
	t_vector	oc = {ray_origin.x - sphere->position[0], ray_origin.y - sphere->position[1], ray_origin.z - sphere->position[2]};
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

//N * (P-P0) = 0
//formula for the plane.
//N is the normalized vector used to check if anything is perpendicular to it
int plane_hit(t_shape *plane, t_vector ray_origin, t_vector ray_dir, float *t)
{
    float denom = plane->vectors[0]*ray_dir.x +\
                  plane->vectors[1]*ray_dir.y +\
                  plane->vectors[2]*ray_dir.z;
    if (fabs(denom) < 1e-6)
        return 0;
    t_vector P0_O = {plane->position[0] - ray_origin.x,\
                     plane->position[1] - ray_origin.y,\
                     plane->position[2] - ray_origin.z};
    *t = P0_O.x*plane->vectors[0] + P0_O.y*plane->vectors[1] + P0_O.z*plane->vectors[2];
    *t /= denom;
    return (*t > 0);
}

void	raytracing(t_data *all)
{
	int		x;
	int		y;
	float	u;
	float	v;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((x + 0.5f) / WIDTH - 0.5f) * all->camera->viewport_w;
			v = ((y + 0.5f) / HEIGHT - 0.5f) * all->camera->viewport_h;
      t_vector ray_origin = {
            all->camera->position[0],
            all->camera->position[1],
            all->camera->position[2]};
        t_vector forward = {
            all->camera->orientation[0],
            all->camera->orientation[1],
            all->camera->orientation[2]};
        t_vector world_up;
        if (fabs(forward.y) > 0.999)
          world_up = (t_vector){1,0,0};
        else
          world_up = (t_vector){0,1,0};
        t_vector right = {
            world_up.y * forward.z - world_up.z * forward.y,
            world_up.z * forward.x - world_up.x * forward.z,
            world_up.x * forward.y - world_up.y * forward.x
        };
        normalize(&right);
        t_vector up = {
            right.y * forward.z - right.z * forward.y,
            right.z * forward.x - right.x * forward.z,
            right.x * forward.y - right.y * forward.x
        };
        normalize(&up);
        t_vector ray_dir = {
            forward.x + u * right.x + v * up.x,
            forward.y + u * right.y + v * up.y,
            forward.z + u * right.z + v * up.z
        };
        normalize(&ray_dir);
			float closest_t = 1e30;
			t_shape *hit_shape = NULL;
			t_vector hit_normal;
			float t_tmp;
			t_list *node = all->shape_list;
			while (node)
			{
				if (node->shape->shape == SPHERE)
				{
					if (sphere_hit(node->shape, ray_origin, ray_dir, &t_tmp) && t_tmp < closest_t)
					{
						closest_t = t_tmp;
						hit_shape = node->shape;

						hit_normal.x = ray_origin.x + t_tmp*ray_dir.x - node->shape->position[0];
						hit_normal.y = ray_origin.y + t_tmp*ray_dir.y - node->shape->position[1];
						hit_normal.z = ray_origin.z + t_tmp*ray_dir.z - node->shape->position[2];
						normalize(&hit_normal);
					}
				}
				else if (node->shape->shape == PLANE)
				{
					if (plane_hit(node->shape, ray_origin, ray_dir, &t_tmp) && t_tmp < closest_t)
					{
						closest_t = t_tmp;
						hit_shape = node->shape;

						hit_normal.x = node->shape->vectors[0];
						hit_normal.y = node->shape->vectors[1];
						hit_normal.z = node->shape->vectors[2];
            normalize(&hit_normal);
					}
				}
				node = node->next;
			}

			if (hit_shape)
			{
				t_vector hit_point = {
					ray_origin.x + closest_t*ray_dir.x,
					ray_origin.y + closest_t*ray_dir.y,
					ray_origin.z + closest_t*ray_dir.z
				};
				t_vector light_dir = {
					all->light->position[0] - hit_point.x,
					all->light->position[1] - hit_point.y,
					all->light->position[2] - hit_point.z
				};
				float light_distance = sqrt(light_dir.x*light_dir.x + light_dir.y*light_dir.y + light_dir.z*light_dir.z);
				normalize(&light_dir);
				t_vector shadow_origin = {
					hit_point.x + hit_normal.x * 0.001f,
					hit_point.y + hit_normal.y * 0.001f,
					hit_point.z + hit_normal.z * 0.001f
				};
				float shadow_t;
				int in_shadow = 0;
				node = all->shape_list;
				while (node)
				{
					if ((node->shape->shape == SPHERE && sphere_hit(node->shape, shadow_origin, light_dir, &shadow_t) && shadow_t < light_distance) ||
						(node->shape->shape == PLANE  && plane_hit(node->shape, shadow_origin, light_dir, &shadow_t) && shadow_t < light_distance))
					{
						in_shadow = 1;
						break;
					}
					node = node->next;
				}
        float diffuse = hit_normal.x*light_dir.x +
                hit_normal.y*light_dir.y +
                hit_normal.z*light_dir.z;
        if (diffuse < 0)
            diffuse = 0;
        float shadow_factor = 1.0f;
        if (in_shadow)
            shadow_factor = 0.3f;

        diffuse *= all->light->brightness * shadow_factor;

        float intensity = all->ambience->ratio + diffuse;
        if (intensity > 1.0f)
            intensity = 1.0f;
				int r = (int)(hit_shape->colour[0] * intensity);
				int g = (int)(hit_shape->colour[1] * intensity);
				int b = (int)(hit_shape->colour[2] * intensity);
				int color = (r << 16) | (g << 8) | b;
				mlx_pixel_put(all->mlx_data->mlx_instance, all->mlx_data->window, x, y, color);
			}
			else
			{
				mlx_pixel_put(all->mlx_data->mlx_instance, all->mlx_data->window, x, y, 0x000000);
			}
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

int	start_raytracing(t_data *all)
{
	// t_data	all;

	// init(all);
	all->camera->fov_rad = all->camera->fov * M_PI / 180.0;
	all->camera->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	all->camera->viewport_h = 2.0 * tan(all->camera->fov_rad / 2.0);
	all->camera->viewport_w = all->camera->viewport_h * all->camera->aspect_ratio;
	raytracing(all);
	return (0);

}
