/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 14:50:07 by skirwan           #+#    #+#             */
/*   Updated: 2025/04/15 15:42:02 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	clean_buffer(char *buffer)
{
	char	*ptr;

	ptr = ft_strchr(buffer, '\n');
	if (ptr == NULL)
	{
		*buffer = 0;
		return ;
	}
	ptr++;
	ft_memmove(buffer, ptr, (BUFFER_SIZE - (ptr - buffer) + 1));
}

char	*gnl_join(char *s1, char *s2)
{
	char	*str;

	if (s1 == NULL)
	{
		str = ft_strdup(s2);
		return (str);
	}
	str = ft_strjoin(s1, s2);
	free(s1);
	return (str);
}

char	*strip_past_nl(char *line)
{
	int		i;
	char	*str;

	i = 0;
	while (line[i] != '\n' && line[i])
		i++;
	if (line[i] == '\0')
		return (line);
	line[i + 1] = '\0';
	str = ft_strdup(line);
	free(line);
	return (str);
}

char	*read_loop(int fd, char *buffer, char *str, ssize_t bytes_read)
{
	while (1)
	{
		buffer[bytes_read] = '\0';
		str = gnl_join(str, buffer);
		if (ft_strchr(str, '\n') || bytes_read < BUFFER_SIZE)
			return (str);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (NULL);
	}
}

char	*read_file(int fd, char *buffer)
{
	ssize_t	bytes_read;
	char	*str;

	str = NULL;
	if (*buffer != 0)
	{
		str = gnl_join(str, buffer);
		if (ft_strchr(str, '\n'))
			return (str);
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read <= 0)
	{
		if (!(bytes_read == 0 && str != NULL))
			return (NULL);
	}
	str = read_loop(fd, buffer, str, bytes_read);
	return (str);
}
