/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:03 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/20 13:57:02 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buffer_allocation(int fd, char **buffer, char **stash)
{
	int i;
	int	strlen;
	int sz;

	i = 0;

	sz = read(fd, *buffer, BUFFER_SIZE);
	printf("sz: %i\n", sz);
	if (sz < 0)
		return (0);
	strlen = ft_strlen(*stash);
	while (i < sz)
	{
		stash[0][i + strlen] = buffer[0][i];
		i++;
	}
	return (1);
}

int	check_current_stash(char *stash)
{
	int i;

	i = 0;
	while(stash && stash[i])
	{
		if (stash[i] == 10)
			return (i);
		i++;
	}
	return (0);
}

int	init(char **buffer, char **stash)
{
	*buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (0);
	clean_buffer(*buffer);
	if (*stash == NULL)
	{
		*stash = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!*stash)
		{
			free(*buffer);
			return (0);
		}
		stash[BUFFER_SIZE] = 0;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	char			*line = NULL;
	char			*buffer = NULL;
	static char		*stash = NULL;
	int				brk_line;
	int				alloc;

	brk_line = 0;
	alloc = 1;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!init(&buffer, &stash))
		return (NULL);
	brk_line = check_current_stash(stash);
	while(!brk_line)
	{
		alloc = buffer_allocation(fd,&buffer, &stash);
		if (!alloc)
		{
			free(stash);
			free(buffer);
			return (NULL);
		}
		brk_line = check_current_stash(stash);
	}
	line = ft_substr(stash, 0, brk_line + 1);
	stash = ft_substr(stash, brk_line + 1, ft_strlen(stash));
	free(buffer);
	return (line);
}

int	main(void)
{
	char		*res;
	int			fd;

	fd = open("./tmp.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("output = %s\n", res);
	res = get_next_line(fd);
	printf("output = %s\n", res);
	res = get_next_line(fd);
	printf("output = %s\n", res);
	return (0);
}