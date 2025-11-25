/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_light.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:54:52 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 15:16:13 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"
#include "parsing.h"

void	read_light(t_data *data, t_parser *parser, int scene_fd)
{
	if (parser->light != 0)
		exit(EXIT_FAILURE); // Only one light element allowed
	
}
