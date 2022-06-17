/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:55:03 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/17 14:07:27 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	buffer_allocation(int fd, char *buffer, char *stash)
{
	int j;
	int	strlen;
	int flag;
	int sz;

	flag = 0;
	j = 0;
	// printf("x\n");
	sz = read(fd, buffer, BUFFER_SIZE);
	// printf("y\n");
	// printf("%i\n", sz);
	strlen = ft_strlen(stash);
	// printf("x\n");
	// printf("Stash length: %i\n", strlen);
	while (j < sz)
	{
		// printf("u\n");
		// printf("u\n");
		// printf("%c\n", buffer[0]);
		if (buffer[j] == 10)
				flag = 1;
		// printf("j + strlen: %i\n", j + strlen);
		stash[j + strlen] = buffer[j];
		stash[j + strlen + 1] = 0;
		j++;
		// printf("x\n");
	}
	if (flag == 1 || sz == 0)
	{
		clean_buffer(buffer);
		return ;
	}
	clean_buffer(buffer);
	buffer_allocation(fd, buffer, stash);
	return ;
}

int	check_current_stash(char *stash)
{
	int i;

	i = 0;
	while(stash[i])
	{
		if (stash[i] == 10)
			return (i);
		i++;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	char			*line;
	char			*buffer = NULL;
	static char		*stash = NULL;
	int				previous_flag;

	// printf("1\n");
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	// printf("2\n");
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	// printf("3\n");
	if (stash == NULL)
	{
		stash = (char *)malloc(sizeof(char) * 1000);
		if (!stash)
			return (NULL);
		stash[0] = 0;
	}
	// printf("4\n");
	previous_flag = check_current_stash(stash);
	if (previous_flag)
	{
		line = ft_substr(stash, 0, previous_flag + 1);
		stash = ft_substr(stash, previous_flag + 1, ft_strlen(stash));
		free(buffer);
		return (line);
	}
	// printf("5\n");
	buffer_allocation(fd, buffer, stash);
	// printf("6\n");
	previous_flag = check_current_stash(stash);
	if (previous_flag)
	{
		line = ft_substr(stash, 0, previous_flag + 1);
		stash = ft_substr(stash, previous_flag + 1, ft_strlen(stash));
		free(buffer);
		return (line);
	}
	line = stash;
	free(buffer);
	return (line);
}

int	main(void)
{
	char	*res;
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
