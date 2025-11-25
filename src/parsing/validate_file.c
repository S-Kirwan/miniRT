/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skirwan <skirwan@student.42london.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:43:35 by skirwan           #+#    #+#             */
/*   Updated: 2025/11/25 13:06:10 by skirwan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "miniRT.h"
#include "parsing.h"

void	write_error(char *error_msg)
{
	write(STDERR_FILENO, "Error\n", 7);
	write(STDERR_FILENO, error_msg, ft_strlen(error_msg));
	write(STDERR_FILENO, "\n", 1);
}

// Checks that the file provided ends with the .rt extension
// If the length of the file is 3 or less characters, it cannot have a name
// and the .rt extension, so it is invalid
int	validate_file_name(char *file_name)
{
	int	length;
	int	i;

	length = ft_strlen(file_name);
	if (length <= 3)
		return (-1);
	i = 0;
	while (i < length - 3)
		i++;
	if (ft_strncmp(file_name + i, ".rt", 3) != 0)
		return (-1);
	return (0);
}

// We only accept one argument, that must end with .rt
// If we fail to open the provided file we exit, printing the error set
// in errno by open
int	validate_file(int argc, char **argv)
{
	int		fd;

	if (argc > 2)
		return (write_error("Too many arguments"), -1);
	else if (argc < 2)
		return (write_error("Please enter a .rt scene"), -1);
	if (validate_file_name(argv[1]) == -1)
		return (write_error("Please enter a valid file ending with .rt"), -1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (perror("Error\n"), -1);
	return (0);
}
