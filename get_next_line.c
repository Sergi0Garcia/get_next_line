/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:03 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/16 14:55:00 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buffer_allocation(int fd, char *buffer, char *stash)
{
	int	i;
	int	sz;
	int	strlen;
	int flag;

	i = 0;
	flag = 0;
	sz = read(fd, buffer, BUFFER_SIZE);
	printf("SZ BUFFER: %s\n", buffer);
	strlen = ft_strlen(stash);
	while (sz > 0)
	{
		while (buffer[i])
		{
			if (buffer[i] == 10)
				flag = i;
			stash[i + strlen] = buffer[i];
			stash[i + strlen + 1] = 0;
			i++;
		}
		if (flag != 0)
			return (flag);
		clean_buffer(buffer);
		buffer_allocation(fd, buffer, stash);
		return (0);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*stash;
	int				has_flag;

	printf("STASH: %s\n", stash);
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	stash = (char *)malloc(sizeof(char) * 1000);
	if (!stash)
		return (NULL);
	stash[0] = 0;
	has_flag = buffer_allocation(fd, buffer, stash);
	if (has_flag)
	{
		line = ft_substr(stash, 0, has_flag + 1);
		stash = ft_substr(stash, has_flag + 1, ft_strlen(stash));
	}
	else
		line = stash;
	return (line);
}

int	main(void)
{
	const char	*res;
	int			fd;

	fd = open("./tmp.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("%s\n", res);
	res = get_next_line(fd);
	printf("%s\n", res);
	res = get_next_line(fd);
	printf("%s\n", res);
	return (0);
}
