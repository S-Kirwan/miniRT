/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tests.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/06 09:13:49 by skirwan           #+#    #+#             */
/*   Updated: 2026/01/06 09:22:03 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"
#include <stdio.h>

void	print_shape_list(t_list *shape_list)
{
	int	i;

	while (shape_list != NULL)
	{
		printf("Shape = %d\n", shape_list->shape->shape);
		printf("Shape colour = ");
		i = 0;
		while (i < 3)
		{
			printf("%d, ", shape_list->shape->colour[i]);
			i++;
		}
		printf("\n");
		shape_list = shape_list->next;
	}
}

void	print_vectors_test(float vectors[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Vector %d = %f\n", i, vectors[i]);
		i++;
	}
}

void	print_coords_test(float coords[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Coord %d = %f\n", i, coords[i]);
		i++;
	}
}

void	print_colours_test(int colours[3])
{
	int	i;

	i = 0;
	while (i < 3)
	{
		printf("Colour %d = %d\n", i, colours[i]);
		i++;
	}
}
