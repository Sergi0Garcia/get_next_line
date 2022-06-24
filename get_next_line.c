/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:32:26 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/24 10:37:59 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	init(char **buffer, char **stash)
{
	if (*stash == NULL)
		*stash = "";
	if (*buffer == NULL)
	{
		*buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!*buffer)
			return (0);
		clean_buffer(*buffer);
	}
	return (1);
}

int	check_current_stash(char *stash)
{
	int i;

	i = 0;
	// printf("1: ft_strlen [%i]\n", (int)ft_strlen(stash));
	while(stash && stash[i] && ft_strlen(stash))
	{
		// printf("i: %i\n", i);
		if (stash[i] == 10)
			return (i);
		i++;
	}
	// printf("Bye\n");
	return (0);
}

int	buffer_allocation(int fd, char **buffer, char **stash)
{
	int i;
	int sz;
	char	*tmp;

	i = 0;
	// printf("x\n");
	clean_buffer(*buffer);
	// printf("xx\n");
	sz = read(fd, *buffer, BUFFER_SIZE);
	// printf("SZ: %i - BUFFER: %c \n", sz, *buffer[0]);
	// printf("xxx\n");
	if (sz < 0)
		return (0);
	if (sz == 0)
		return (2);
	// printf("(int)ft_strlen(stash): %i\n", (int)ft_strlen(*stash));
	tmp = ft_strjoin(*stash, *buffer, sz);
	// printf("tmp: %s\n", tmp);
	*stash = tmp;
	free(tmp);
	tmp = NULL;
	// printf("Len[%i] - Stash: %s\n", (int)ft_strlen(*stash), *stash);
	// printf("xxxxx\n");
	return (1);
}

void moveptr(char **line, char *res)
{
	*line = res;
	free(res);
	res = NULL;
}

char	*get_next_line(int fd)
{
	char			*line = NULL;
	char			*buffer = NULL;
	static char		*stash = NULL;
	int				brk_line;
	int				end_file;
	int 			alloc;
	char			*tmp;

	end_file = 0;
	alloc = 0;
	// printf("1\n");
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!init(&buffer, &stash))
		return (NULL);
	// printf("2\n");
	brk_line = check_current_stash(stash);
	// printf("3\n");
	// printf("brkline1: %i\n", brk_line);
	if (brk_line)
	{
		// printf("o-\n");
		line = ft_substr(stash, 0, brk_line  + 1);
		// printf("o\n");
		stash = ft_substr(stash, brk_line + 1, ft_strlen(stash));
		// printf("z\n");
		free(buffer);
		buffer = NULL;
		return (line);
	}
	// printf("4\n");
	while(!brk_line && !end_file)
	{
		// printf("5\n");
		// printf("PLine: %p\n", line);
		// printf("PBuffer: %p\n", buffer);
		// printf("PStash: %p\n", stash);
		alloc = buffer_allocation(fd, &buffer, &stash);
		// printf("6\n");
		// printf("alloc: %i\n", alloc);
		if (alloc == 0)
		{
			free(buffer);
			buffer = NULL;
			free(line);
			line = NULL;
			return (NULL);
		}
		// printf("7\n");
		if (alloc == 2)
			end_file = 1;
		if (alloc == 1)
			brk_line = check_current_stash(stash);
	}
	// printf("PLine: %p\n", line);
	// printf("PBuffer: %p\n", buffer);
	// printf("w\n");
	if (ft_strlen(stash))
	{
		// printf("8\n");
		// printf("q\n");
		if (end_file)
			brk_line = ft_strlen(stash);
		tmp = ft_substr(stash, 0, brk_line  + 1);
		moveptr(&line, tmp);
		stash = ft_substr(stash, brk_line + 1, ft_strlen(stash));
	}
	free(buffer);
	buffer = NULL;
	return (line);
}

// int	main(void)
// {
// 	char		*res;
// 	int			fd;

// 	fd = open("./gnlTester/files/nl", O_RDONLY);
// 	// fd = open("./tmp.txt", O_RDONLY);
// 	res = get_next_line(fd);
// 	printf("output 1 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	// res = get_next_line(fd);
// 	// printf("output 2 = %s-\n", res);
// 	return (0);
// }