/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_camera.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:40:37 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 14:41:43 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

void	read_camera(t_data *data, t_parser *parser, int scene_fd)
{
	if (parser->camera != 0)
		exit(EXIT_FAILURE); // Only one camera element allowed
}
