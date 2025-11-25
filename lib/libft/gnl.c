/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 12:49:33 by skirwan           #+#    #+#             */
/*   Updated: 2025/04/15 15:37:55 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1] = {0};
	char		*line;

	if (fd < 0 || fd > MAX_OPEN || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_file(fd, buffer);
	if (line == NULL)
		return (line);
	line = strip_past_nl(line);
	clean_buffer(buffer);
	return (line);
}
