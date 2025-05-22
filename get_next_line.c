/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-houa <mel-houa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 21:55:49 by mel-houa          #+#    #+#             */
/*   Updated: 2024/12/23 22:59:58 by mel-houa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

static char	*ft_read_and_fill(int fd, char *last)
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
	static char	*last;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	last = ft_read_and_fill(fd, last);
	if (!last)
		return (NULL);
	line = ft_get_filtered_line(last);
	last = ft_get_next_start(last);
	return (line);
}
// #include <stdio.h>

// int main()
// {
//     int fd = open("test1.txt", O_RDONLY);
//     char *line;
// //  printf("%d", printf("%s", get_next_line(fd)));
//     // printf("%s", get_next_line(fd));

//    printf("Reading lines from file:\n");
//     while ((line = get_next_line(fd)))
//     {
//         printf("%s", line);
//        free(line);
//     }
//     close(fd);
//     return (0);
// }
