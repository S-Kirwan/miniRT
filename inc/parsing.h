/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:28 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 13:06:09 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "miniRT.h"

typedef struct s_parser
{
	int	ambience;
	int	camera;
	int	light;
	int	spheres;
	int	planes;
	int	cylinders;
}	t_parser;

int	validate_file(int argc, char **argv);

#endif

