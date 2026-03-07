/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 17:19:09 by skirwan           #+#    #+#             */
/*   Updated: 2026/03/04 18:55:18 by aramos           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "mlx.h"
#include "window_management.h"

//Changed from mlx_hook(mlx_data->window, 2, (1L<<0), key_press_event, mlx_data);
//to:
//mlx_hook(mlx_data->window, 2, (1L<<0), (int (*)())key_press_event, mlx_data);
void	close_window_hooks(t_data *all)//, t_mlx_data *mlx_data)
{
	mlx_hook(all->mlx_data->window, 2, (1L<<0), key_press_event, all);
	mlx_hook(all->mlx_data->window, 17, 0L, full_exit, all);
}
