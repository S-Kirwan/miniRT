/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aramos <alejandro.ramos.gua@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/12 15:07:13 by aramos            #+#    #+#             */
/*   Updated: 2026/02/12 15:08:24 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACING_H
# define RAYTRACING_H

# include <math.h>
# include "libft.h"
# include "miniRT.h"

void	raytracing(t_data *all);
int		sphere_hit(t_shape *sphere, t_vector ray_origin, t_vector ray_dir, float *t);

#endif
