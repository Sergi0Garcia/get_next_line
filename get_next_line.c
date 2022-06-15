/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:03 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/15 13:20:58 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

void	buffer_allocation(int fd, char *buffer)
{
	int	i;
	int	sz;

	i = 0;
	sz = read(fd, buffer, BUFFER_SIZE);
	while (sz > 0)
	{
		while (buffer[i])
		{
			printf("%c\n", buffer[i]);
			i++;
		}
		i = 0;
		buffer_allocation(fd, buffer);
		return ;
	}
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	buffer_allocation(fd, buffer);
	line = "Prueba";
	return (line);
}

int	main(void)
{
	const char	*res;
	int			fd;

	fd = open("./tmp.txt", O_RDONLY);
	res = get_next_line(fd);
	return (0);
}
