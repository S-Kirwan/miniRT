/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_management.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 14:45:36 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 17:48:09 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WINDOW_MANGEMENT_H
# define WINDOW_MANGEMENT_H

# include "miniRT.h"
# include "mlx.h"

# ifndef WIDTH
#  define WIDTH 1000
# endif

# ifndef HEIGHT
#  define HEIGHT 1000
# endif

# define ESC 0xff1b

// window_initialisation.c
void	initialise_mlx(t_mlx_data *mlx_data);

// image_initialisation.c
int		calculate_img_offset(int line_length, int bpp, int x, int y);
void	create_mlx_img(t_mlx_img *mlx_img, void *mlx_instance);

// window_destruction.c
int	destroy_window(int keycode, t_mlx_data *mlx_data);

// event_hooks.c
void	close_window_hooks(t_mlx_data *mlx_data);
int	key_press_event(int keycode, t_mlx_data *mlx_data);
#endif
