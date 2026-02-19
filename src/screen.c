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

void  array_to_vector(float source[3], t_vector *dest)
{
  dest->x = source[0];
  dest->y = source[1];
  dest->z = source[2];
}

void  cross_product(t_vector *a, t_vector *b, t_vector *result, int up)
{
  result->x = a->y * b->z - a->z * b->y;
  if (!up)
  {
    result->y = a->x * b->z - a->x * b->z;
    result->z = a->x * b->y - a->x * b->y;
  }
  else if (up == 1) 
  {
    result->y = a->z * b->x - a->x * b->z;
    result->z = a->x * b->y - a->y * b->x;
  }
}

void  get_world_up(t_data *all)
{
  if (fabs(all->rt->forward->y) > 0.999)
  {
    all->rt->world_up->x = 1;
    all->rt->world_up->y = 0;
    all->rt->world_up->z = 0;
  }
  else
  {
    all->rt->world_up->x = 0;
    all->rt->world_up->y = 1;
    all->rt->world_up->z = 0;
  }
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
      array_to_vector(all->camera->position, all->rt->ray_origin);
      array_to_vector(all->camera->orientation, all->rt->forward);
      get_world_up(all);
      cross_product(all->rt->world_up, all->rt->forward, all->rt->right, 0);
      cross_product(all->rt->right, all->rt->forward, all->rt->up, 1);
      normalize(all->rt->right);
      normalize(all->rt->up);
      t_vector ray_dir = {
          all->rt->forward->x + u * all->rt->right->x + v * all->rt->up->x,
          all->rt->forward->y + u * all->rt->right->y + v * all->rt->up->y,
          all->rt->forward->z + u * all->rt->right->z + v * all->rt->up->z
      };
      normalize(&ray_dir);
      //TODO: Clean from here
			float closest_t = 1e30;
			t_shape *hit_shape = NULL;
			t_vector hit_normal;
			float t_tmp;
			t_list *node = all->shape_list;
			while (node)
			{
				if (node->shape->shape == SPHERE)
				{
					if (sphere_hit(node->shape, *(all->rt->ray_origin), ray_dir, &t_tmp) && t_tmp < closest_t)
					{
						closest_t = t_tmp;
						hit_shape = node->shape;

						hit_normal.x = all->rt->ray_origin->x + t_tmp*ray_dir.x - node->shape->position[0];
						hit_normal.y = all->rt->ray_origin->y + t_tmp*ray_dir.y - node->shape->position[1];
						hit_normal.z = all->rt->ray_origin->z + t_tmp*ray_dir.z - node->shape->position[2];
						normalize(&hit_normal);
					}
				}
				else if (node->shape->shape == PLANE)
				{
					if (plane_hit(node->shape, *(all->rt->ray_origin), ray_dir, &t_tmp) && t_tmp < closest_t)
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
					all->rt->ray_origin->x + closest_t*ray_dir.x,
					all->rt->ray_origin->y + closest_t*ray_dir.y,
					all->rt->ray_origin->z + closest_t*ray_dir.z
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
  all->rt = malloc(sizeof(t_raytracing));
  all->rt->ray_origin = malloc(sizeof(t_vector));
  all->rt->forward = malloc(sizeof(t_vector));
  all->rt->right = malloc(sizeof(t_vector));
  all->rt->up = malloc(sizeof(t_vector));
  all->rt->world_up = malloc(sizeof(t_vector));
	raytracing(all);
	return (0);

}
