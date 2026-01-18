/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_destruction.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:20:54 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 17:46:52 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"

int	key_press_event(int keycode, t_mlx_data *mlx_data)
{
	if (keycode == ESC)
		mlx_destroy_window(mlx_data->mlx_instance, mlx_data->window);

	return (0);
}
