/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:11:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/07 11:12:39 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

int	check_current_stash(char *stash)
{
	int	i;

	i = 0;
	while (stash && stash[i])
	{
		if (stash[i] == 10)
			return (i);
		i++;
	}
	return (-1);
}


char	*get_next_line(int fd)
{
	char			*line;
	char			*buf;
	static char		*stash;
	int				ret;
	int				brk_line;
	int				real_brkline;
	char 			*tmp;
	char 			*tmp2;


	brk_line = -1;
	ret = BUFFER_SIZE;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	brk_line = check_current_stash(stash);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (brk_line == -1 && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		if (ret == 0)
		{
			if (!ft_strlen(stash))
			{
				free(buf);
				return (NULL);
			}
			break ;
		}
		buf[ret] = '\0';
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		free(tmp);
		brk_line = check_current_stash(stash);
		if (brk_line != -1)
			break ;
	}
	free(buf);
	real_brkline = brk_line;
	if (real_brkline == -1)
		real_brkline = ft_strlen(stash);
	tmp2 = stash;
	line = ft_substr(tmp2, 0, real_brkline + 1);
	tmp = stash;
	stash = ft_substr(tmp, real_brkline + 1, ft_strlen(tmp));
	free(tmp);
	return (line);
}

int	main(void)
{
	char		*res;
	int			fd;

	// fd = open("/Users/segarcia/Desktop/42/get_next_line_gh/gnlTester/files/nl", O_RDONLY);
	fd = open("./tmp.txt", O_RDONLY);
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