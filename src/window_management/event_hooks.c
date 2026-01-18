/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:19:09 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/18 17:48:20 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"

void	close_window_hooks(t_mlx_data *mlx_data)
{
	mlx_hook(mlx_data->window, 2, (1L<<0), key_press_event, mlx_data);
}
