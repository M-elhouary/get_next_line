/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:56:20 by mel-houa          #+#    #+#             */
/*   Updated: 2024/12/22 22:33:22 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_get_next_start(char *last)
{
	int		i;
	int		j;
	char	*next_start;

	i = 0;
	j = 0;
	if (!last)
		return (NULL);
	while (last[i] && last[i] != '\n')
		i++;
	if (!last[i])
	{
		free(last);
		return (NULL);
	}
	next_start = malloc(ft_strlen(last) - i);
	if (!next_start)
		return (NULL);
	i++;
	while (last[i])
		next_start[j++] = last[i++];
	next_start[j] = '\0';
	free(last);
	return (next_start);
}

static char	*ft_get_filtered_line(char *line)
{
	char	*filtered;
	int		i;

	i = 0;
	if (!line || !*line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	filtered = malloc(i + 1);
	if (!filtered)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		filtered[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		filtered[i++] = '\n';
	filtered[i] = '\0';
	return (filtered);
}

char	*ft_read_and_fill(int fd, char *last)
{
	char	*buffer;
	ssize_t	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	while (!ft_strchr(last, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read <= 0)
		{
			if (!last || !*last)
			{
				free(last);
				free(buffer);
				return (NULL);
			}
			break ;
		}
		buffer[bytes_read] = '\0';
		last = ft_free(last, buffer);
	}
	free(buffer);
	return (last);
}

char	*get_next_line(int fd)
{
	static char	*last[MAX_OPEN];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_OPEN)
		return (NULL);
	last[fd] = ft_read_and_fill(fd, last[fd]);
	if (!last[fd])
		return (NULL);
	line = ft_get_filtered_line(last[fd]);
	last[fd] = ft_get_next_start(last[fd]);
	return (line);
}

// #include <stdio.h>

// int main() {
//     int fd1, fd2;
//     char *line1, *line2;

//     // Open two test files (replace with actual file paths)
//     fd1 = open("file1.txt", O_RDONLY);
//     fd2 = open("file2.txt", O_RDONLY);

//     // Check if files are opened successfully
//     if (fd1 == -1 || fd2 == -1) {
//         perror("Failed to open files");
//         return (1);
//     }

//     // Read and print lines from the first file
//     printf("File 1:\n");
//     while ((line1 = get_next_line_bonus(fd1)) != NULL) {
//         printf("%s", line1);
//         free(line1);  // Free the line after use to avoid memory leaks
//     }

//     // Read and print lines from the second file
//     printf("\nFile 2:\n");
//     while ((line2 = get_next_line_bonus(fd2)) != NULL) {
//         printf("%s", line2);
//         free(line2);  // Free the line after use to avoid memory leaks
//     }

//     // Close the files after reading
//     close(fd1);
//     close(fd2);

//     return (0);
// }
