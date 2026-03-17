/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:45:36 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/04 18:54:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_MANAGEMENT_H
# define WINDOW_MANAGEMENT_H

# include "miniRT.h"
# include "mlx.h"

# ifndef WIDTH
#  define WIDTH 1920
# endif

# ifndef HEIGHT
#  define HEIGHT 1080
# endif

# define ESC 0xff1b

// window_initialisation.c
void	initialise_mlx(t_data *all);

// image_initialisation.c
int		calculate_img_offset(int line_length, int bpp, int x, int y);
void	place_pixel_to_img(t_mlx_img *mlx_img, int x, int y, int colour);
void	create_mlx_img(t_mlx_img *mlx_img, void *mlx_instance);

// window_destruction.c
int		full_exit(t_data *all);
void	free_shape_list(t_data *all);
int		key_press_event(int keycode, t_data *all);

// event_hooks.c
void	close_window_hooks(t_data *all);

#endif
