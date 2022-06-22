/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:03 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/22 13:35:52 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	buffer_allocation(int fd, char *buffer, char **stash)
{
	int i;
	int sz;

	i = 0;
	clean_buffer(buffer);
	sz = read(fd, buffer, BUFFER_SIZE);
	if (sz < 0)
		return (0);
	if (sz == 0)
		return (2);
	*stash = ft_strjoin(*stash, buffer, sz);
	// printf("stash: %s\n", *stash);
	return (1);
}

int	check_current_stash(char *stash)
{
	int i;

	i = 0;

	while(stash && ft_strlen(stash) && stash[i] )
	{
		if (stash[i] == 10)
			return (i);
		i++;
	}
	return (0);
}

int	init(char **buffer, char **stash)
{
	if (*stash == NULL)
		*stash = "";
	if (*buffer == NULL)
	{
		*buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!*buffer)
			return (0);
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
	int				real_brkl;

	brk_line = 0;
	alloc = 0;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!init(&buffer, &stash))
		return (NULL);
	brk_line = check_current_stash(stash);
	while(!brk_line)
	{
		// printf("x\n");
		alloc = buffer_allocation(fd, buffer, &stash);
		if (!alloc)
		{
			free(buffer);
			return (NULL);
		}
		if (alloc == 1)
		{
			brk_line = check_current_stash(stash);
			real_brkl = brk_line;
		}
		if (alloc == 2)
		{
			brk_line = 1;
			real_brkl = ft_strlen(stash);
		}
	}
	if (ft_strlen(stash))
	{
		// printf("here\n");
		line = ft_substr(stash, 0, real_brkl  + 1);
		// printf("Line: %s\n", line);
		stash = ft_substr(stash, real_brkl + 1, ft_strlen(stash));
	}
	free(buffer);
	return (line);
}

// int	main(void)
// {
// 	char		*res;
// 	int			fd;

// 	fd = open("./tmp.txt", O_RDONLY);
// 	res = get_next_line(fd);
// 	printf("output 1 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	return (0);
// }