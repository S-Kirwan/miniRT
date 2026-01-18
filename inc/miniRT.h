/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:44:15 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 16:14:49 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <fcntl.h>
# include <sys/stat.h>
# include "mlx.h"

typedef struct s_list
{
	union
	{
		struct s_shape	*shape;
		void			*content;
		int				nbr;
		char			*str;
	};
	struct s_list	*next;
}					t_list;

typedef enum e_shape
{
	CYLINDER,
	PLANE,
	SPHERE
}	t_en_shape;

typedef struct	s_vector//Struct to do math and store temp values
{
	float	x;
	float	y;
	float	z;
	// int		p;//1 if its a point, 0 if its a vector(with direction)
}	t_vector;

typedef struct s_shape
{
	t_en_shape	shape;
	float	position[3];
	float	vectors[3];
	float	diameter;
	float	height;
	int		colour[3];
}	t_shape;

typedef struct s_ambience
{
	float	ratio;
	int		colour[3];
}	t_ambience;

typedef struct s_camera
{
	float	orientation[3];
	float	aspect_ratio;
	float	position[3];
	float	viewport_h;
	float	viewport_w;
	float	fov_rad;
	int		fov;
}	t_camera;

typedef struct s_light
{
	float	position[3];
	float	brightness;
	int		colour[3];
}	t_light;

typedef struct	s_mlx_img
{
	void	*image;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_mlx_img;

typedef struct s_mlx_data
{
	t_mlx_img	*mlx_img;
	void		*mlx_instance;
	void		*window;

}	t_mlx_data;

// structure has changed post merge therefore current code in src/screen.c will break
typedef struct s_data
{
	t_ambience	*ambience;
	t_mlx_data	*mlx_data;
	t_camera	*camera;
	t_light		*light;
	t_shape		*shapes;
	t_list		*shape_list;
}	t_data;

#endif
