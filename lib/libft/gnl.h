/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:14:50 by skirwan           #+#    #+#             */
/*   Updated: 2025/04/15 15:46:42 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1000
# endif

# ifndef MAX_OPEN
#  define MAX_OPEN 1000
# endif

# include "../../libft/libft.h"

char	*get_next_line(int fd);

char	*read_loop(int fd, char *buffer, char *str, ssize_t bytes_read);
void	clean_buffer(char *buffer);
char	*gnl_join(char *s1, char *s2);
char	*strip_past_nl(char *line);
char	*read_file(int fd, char *buffer);

#endif
