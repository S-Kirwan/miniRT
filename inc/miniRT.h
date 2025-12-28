/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:44:15 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 13:06:08 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "libft.h"

typedef struct s_data
{
	struct s_shp_list	*shapes;
	struct s_ambience	*ambience;
	struct s_camera		*camera;
	struct s_light		*light;
}	t_data;

typedef struct s_shp_list
{
	struct	s_shp_list	*next;
	struct	s_shape		*shape;
}	t_shp_list;

typedef enum e_shape
{
	CYLINDER,
	PLANE,
	SPHERE
}	t_en_shape;

typedef struct s_ambience
{
	float	ratio;
	int		colour[3];
}	t_ambience;

typedef struct s_camera
{
	float	position[3];
	float	orientation[3];
	int		fov;
}	t_camera;

typedef struct s_light
{
	float	position[3];
	float	brightness;
	int		colour[3];
}	t_light;

typedef struct s_shape
{
	t_en_shape	shape;
	float	position[3];
	float	vectors[3];
	float	diameter;
	float	height;
	int		colour[3];
}	t_shape;

#endif
