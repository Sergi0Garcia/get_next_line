/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 11:32:26 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/04 08:27:52 by segarcia         ###   ########.fr       */
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
	while(stash && stash[i])
	{
		if (stash[i] == 10)
			return (i);
		i++;
	}
	return (0);
}

int	buffer_allocation(int fd, char **buffer, char **stash)
{
	int i;
	int sz;

	i = 0;
	clean_buffer(*buffer);
	sz = read(fd, *buffer, BUFFER_SIZE);
	if (sz < 0)
		return (0);
	if (sz == 0)
		return (2);
	*stash = ft_strjoin(*stash, *buffer, sz);
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
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	if (!init(&buffer, &stash))
		return (NULL);
	brk_line = check_current_stash(stash);
	if (brk_line)
	{
		line = ft_substr(stash, 0, brk_line  + 1);
		tmp = ft_substr(stash, brk_line + 1, ft_strlen(stash));
		stash = tmp;
		free(tmp);
		free(buffer);
		buffer = NULL;
		return (line);
	}
	while(!brk_line && !end_file)
	{
		alloc = buffer_allocation(fd, &buffer, &stash);
		if (alloc == 0)
		{
			free(buffer);
			buffer = NULL;
			free(line);
			line = NULL;
			return (NULL);
		}
		if (alloc == 2)
			end_file = 1;
		if (alloc == 1)
		{
			brk_line = check_current_stash(stash);
			if (alloc == 2)
				end_file = 1;
			break;
		}
	}
	if (ft_strlen(stash))
	{
		if (end_file)
			brk_line = ft_strlen(stash);
		tmp = ft_substr(stash, 0, brk_line  + 1);
		moveptr(&line, tmp);
		stash = ft_substr(stash, brk_line + 1, ft_strlen(stash));
	}
	if (buffer)
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
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	res = get_next_line(fd);
// 	printf("output 2 = %s-\n", res);
// 	return (0);
// }