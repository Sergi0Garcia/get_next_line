/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:29:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/07 13:52:39 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	get_nl_idx(char *ptr)
{
	int	i;

	i = 0;
	while (ptr && ptr[i])
	{
		if (ptr[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_get_next_stash(char *stash)
{
	int		i;
	int		brk_idx;
	int		str_len;
	char	*next_stash;

	i = 0;
	brk_idx = 0;
	while (stash[brk_idx] && stash[brk_idx] != '\n')
		brk_idx++;
	if (!stash[brk_idx])
	{
		free(stash);
		return (NULL);
	}
	str_len = ft_strlen(stash);
	next_stash = (char *)malloc(sizeof(char) * (str_len - brk_idx + 1));
	if (!next_stash)
		return (NULL);
	brk_idx++;
	while(stash[brk_idx])
	{
		next_stash[i] = stash[brk_idx];
		brk_idx++;
		i++;
	}
	next_stash[i] = '\0';
	free(stash);
	return (next_stash);
}

static char	*ft_get_line(char *stash)
{
	int		i;
	int		brk_idx;
	char	*str;

	i = 0;
	brk_idx = get_nl_idx(stash);
	if (!stash[i])
		return (NULL);
	if (brk_idx == -1)
	{
		if(!ft_strlen(stash))
			return (NULL);
		brk_idx = ft_strlen(stash);
	}
	str = (char *)malloc(sizeof(char) * brk_idx + 2);
	if (!str)
		return (NULL);
	while(stash[i] && i < brk_idx + 1)
	{
		str[i] = stash[i];
		i++;
	}
	if (stash[i])
	{
		str[i] = stash[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer;
	static char		*stash;
	int				read_nbr;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	read_nbr = BUFFER_SIZE;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while(read_nbr > 0 && get_nl_idx(stash) == -1)
	{
		read_nbr = read(fd, buffer, BUFFER_SIZE);
		if (read_nbr == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[read_nbr] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	line = ft_get_line(stash);
	stash = ft_get_next_stash(stash);
	return (line);
}

int	main(void)
{
	char		*res;
	int			fd;

	fd = open("/Users/segarcia/Desktop/42/get_next_line_gh/gnlTester/files/41_with_nl", O_RDONLY);
	// fd = open("./tmp.txt", O_RDONLY);
	res = get_next_line(fd);
	printf("output 1 = %s-\n", res);
	res = get_next_line(fd);
	printf("output 2 = %s-\n", res);
	res = get_next_line(fd);
	printf("output 3 = %s-\n", res);
	res = get_next_line(fd);
	printf("output 4 = %s-\n", res);
	res = get_next_line(fd);
	printf("output 5 = %s-\n", res);
	system("leaks a.out");
	return (0);
}