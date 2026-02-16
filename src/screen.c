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

//Formula for raytracing is P(t) = O + tD
//O is the camera position (x,y,z)
//D is the orientation vector + pixel offset from camera orientation vector
//t is the distance of the ray
//ray_origin = O
//ray_dir = D
// t = t haha
// __attribute__((optimize("O3")))
// void	raytracing(t_data *all)
// {
// 	t_vector	ray_origin = {all->camera->position[0], all->camera->position[1], all->camera->position[2]};
// 	int		x;
// 	int		y;
// 	float	u;
// 	float	v;
// 	float	t;
// 	float	ambient;
// 	float	intensity;
// 	float	light_distance;
// 	float	shadow;;
//
// 	ambient = all->ambience->ratio;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		x = 0;
// 		while (x < WIDTH)
// 		{
// 			u = ((x + 0.5f) / WIDTH - 0.5f) * all->camera->viewport_w;
// 			v = (0.5f - (y + 0.5f) / HEIGHT) * all->camera->viewport_h;
// 			t_vector	ray_dir = {all->camera->orientation[0] + u, all->camera->orientation[1] + v, all->camera->orientation[2]};
// 			normalize(&ray_dir);
//              if (sphere_hit(all, ray_origin, ray_dir, &t))
// 			{
// 				t_vector	hit_point = {ray_origin.x + t * ray_dir.x, ray_origin.y + t * ray_dir.y, ray_origin.z + t * ray_dir.z};
// 				t_vector	surface_normal = {hit_point.x - all->shape_list->shape->position[0], hit_point.y - all->shape_list->shape->position[1], hit_point.z - all->shape_list->shape->position[2]};
// 				normalize(&surface_normal);
// 				t_vector	light_dir = {all->light->position[0] - hit_point.x, all->light->position[1] - hit_point.y, all->light->position[2] - hit_point.z};
// 				t_vector	shadow_dir = {all->light->position[0] - hit_point.x, all->light->position[1] - hit_point.y, all->light->position[2] - hit_point.z};
// 				light_distance = sqrt(shadow_dir.x * shadow_dir.x + shadow_dir.y * shadow_dir.y + shadow_dir.z * shadow_dir.z);
// 				normalize(&shadow_dir);
// 				normalize(&light_dir);
// 				t_vector shadow_origin = {hit_point.x + surface_normal.x * 0.001f, hit_point.y + surface_normal.y * 0.001f, hit_point.z + surface_normal.z * 0.001f};
// 				float	diffuse = surface_normal.x * light_dir.x + surface_normal.y * light_dir.y + surface_normal.z * light_dir.z;
// 				if (diffuse < 0)
// 					diffuse = 0;
// 				if (sphere_hit(all, shadow_origin, light_dir, &shadow) && shadow < light_distance)
// 					diffuse = 0;
// 				intensity = ambient + diffuse;
// 				if (intensity > 1.0f)
// 					intensity = 1.0f;
// 				int	r = (int)(all->shape_list->shape->colour[0] * intensity);
// 				int	g = (int)(all->shape_list->shape->colour[1] * intensity);
// 				int	b = (int)(all->shape_list->shape->colour[2] * intensity);
// 				int	color = (r << 16) | (g << 8) | b;
//                 mlx_pixel_put(all->mlx_data->mlx_instance, all->mlx_data->window, x, y, color);
//             }
//             else
//              {
//                 mlx_pixel_put(all->mlx_data->mlx_instance, all->mlx_data->window, x, y, 0x000000);
//              }
// 			x++;
// 		}
// 		y++;
// 	}
//
// }

void	raytracing(t_data *all)
{
	int		x;
	int		y;
	float	u;
	float	v;
	float	ambient;

	ambient = all->ambience->ratio;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			u = ((x + 0.5f) / WIDTH - 0.5f) * all->camera->viewport_w;
			v = (0.5f - (y + 0.5f) / HEIGHT) * all->camera->viewport_h;

			t_vector ray_origin = {all->camera->position[0], all->camera->position[1], all->camera->position[2]};
			t_vector ray_dir = {all->camera->orientation[0] + u,
								all->camera->orientation[1] + v,
								all->camera->orientation[2]};
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
				float diffuse = hit_normal.x*light_dir.x + hit_normal.y*light_dir.y + hit_normal.z*light_dir.z;
				if (diffuse < 0)
					diffuse = 0;
				if (in_shadow)
					diffuse = 0;
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
