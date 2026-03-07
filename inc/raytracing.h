/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:07:13 by aramos            #+#    #+#             */
/*   Updated: 2026/03/04 18:35:45 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <math.h>
# include "libft.h"
# include "miniRT.h"

//raytracing.c
int		start_raytracing(t_data *all);

//rt_utils.c

void	array_to_vector(float source[3], t_vector *dest);
void	get_world_up(t_data *all);
void	shape_list_traversal(t_raytracing *rt, t_vector ray_dir, float pos[3]);
void	hit_helper(t_data *all, int x, int y);

//calculations.c
void	cross_product(t_vector *a, t_vector *b, t_vector *result, int up);
void	calculate_offset(t_data *all, t_raytracing *rt, int x, int y);
void	calculate_hit_point(t_raytracing *rt);
void	calculate_light_dir(t_data *all);
void	normalize(t_vector	*v);

//shadows.c
void	throw_shade(t_data *all);
void	calculate_shadow_origin(t_raytracing *rt);
void	calculte_diffuse(t_data *all, int in_shadow);

//color.c
void	color_pixel(t_data *all, int x, int y);

//sphere.c
int		sphere_hit(t_data *all, t_vector ray_origin, \
t_vector ray_dir, float *t);
void	origin_to_center(t_data *all, t_vector ray_o, float *position);

//plane.c
int		plane_hit(t_shape *plane, t_vector ray_o, t_vector ray_dir, float *t);

//cylinder.c
int		cylinder_hit(t_data *all, t_vector ray_o, t_vector ray_dir, float *t);

//free.c
void	free_all(t_data *all);

#endif
