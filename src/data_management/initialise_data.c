/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/08 14:41:35 by skirwan           #+#    #+#             */
/*   Updated: 2026/02/08 15:57:01 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include <stdio.h>
#include <stdlib.h>

int	malloc_error()
{
	perror("Memory error\n");
	return (-1);
}

int	stagger_frees(t_data *data, t_en_bad_allocation failed_allocation)
{
	if (failed_allocation == CAMERA)
		free(data->ambience);
	else if (failed_allocation == LIGHT)
	{
		free(data->ambience);
		free(data->camera);
	}
	else if (failed_allocation == MLX_DATA)
	{
		free(data->ambience);
		free(data->camera);
		free(data->light);
	}
	else if (failed_allocation == MLX_DATA_IMG)
	{
		free(data->ambience);
		free(data->camera);
		free(data->light);
		free(data->mlx_data);
	}
	free(data);
	return (malloc_error());
}

int	initialise_data(t_data **data_ref)
{
	t_data	*data;

	*data_ref = malloc(sizeof(**data_ref));
	data = *data_ref;

	if (data == NULL)
		return (malloc_error());
	data->ambience = malloc(sizeof(*data->ambience));
	if (data->ambience == NULL)
		return (stagger_frees(data, AMBIENCE));
	data->camera = malloc(sizeof(*data->camera));
	if (data->camera == NULL)
		return (stagger_frees(data, CAMERA));
	data->light = malloc(sizeof(*data->light));
	if (data->light == NULL)
		return (stagger_frees(data, LIGHT));
	data->mlx_data = malloc(sizeof(*data->mlx_data));
	if (data->mlx_data == NULL)
		return (stagger_frees(data, MLX_DATA));
	data->mlx_data->mlx_img = malloc(sizeof(*data->mlx_data->mlx_img));
	if (data->mlx_data->mlx_img == NULL)
		return (stagger_frees(data, MLX_DATA_IMG));
	data->shape_list = NULL;
	return (0);
}
