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
# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <sys/stat.h>
# include "libft.h"

typedef struct	s_vector//Struct to do math and store temp values
{
	float	x;
	float	y;
	float	z;
	// int		p;//1 if its a point, 0 if its a vector(with direction)
}	t_vector;

typedef struct s_data
{
	void				*mlx;//to store the minilibx variables in the general one
	void				*win;//same as above
	struct s_ambience	*ambience;
	struct s_camera		*camera;
	struct s_light		*lights;
	struct s_sphere		*spheres;
	struct s_cylinder	*cylinders;
	struct s_plane		*planes;
}	t_data;

// Ratio for the ambience is input from 0 to 1 in the input file, but we
// multiply this by 100 so that we can use an int and not a float
// This may not be helpful at all, subject to change - I just thought ints
// are easier to work with compared to floats where possible
typedef struct s_ambience
{
	int	ratio;
	int	colour[3];
}	t_ambience;

typedef struct s_camera
{
	float		x;
	float		y;
	float		z;
	float		x_orientation;
	float		y_orientation;
	float		z_orientation;
	int			fov;
	float		fov_rad;
	float		aspect_ratio;
	float		viewport_h;
	float		viewport_w;
	t_vector	normal;
}	t_camera;

typedef struct s_light
{
	float	x;
	float	y;
	float	z;
	int		brightness;
	int		red;
	int		green;
	int		blue;
}	t_light;

typedef struct s_sphere
{
	float	x;
	float	y;
	float	z;
	float	diameter;
	int		red;
	int		green;
	int		blue;
}	t_sphere;

typedef struct s_plane
{
	float	x;
	float	y;
	float	z;
	float	x_vector;
	float	y_vector;
	float	z_vector;
	int		red;
	int		green;
	int		blue;
}	t_plane;

typedef struct s_cylinder
{
	float	x;
	float	y;
	float	z;
	float	x_vector;
	float	y_vector;
	float	z_vector;
	float	diameter;
	float	height;
	int		red;
	int		green;
	int		blue;
}	t_cylinder;

#endif
