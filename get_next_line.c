/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 09:11:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/04 11:37:48 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	return (-1);
}

char	*get_next_line(int fd)
{
	char			*line = NULL;
	char			buf[BUFFER_SIZE + 1];
	static char		*stash = "";
	char			*tmp;
	int				ret;
	int				brk_line;
	int 			real_brkline;

	brk_line = -1;
	ret = BUFFER_SIZE;
	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	brk_line = check_current_stash(stash);
	while (brk_line == -1 && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		if (!ret)
		{
			if (!ft_strlen(stash))
				return (NULL);
			break;
		}
		buf[ret] = 0;
		tmp = stash;
		stash = ft_strjoin(tmp, buf);
		brk_line = check_current_stash(stash);
		if (brk_line != -1)
			break ;
	}
	real_brkline = brk_line;
	if (real_brkline == -1)
		real_brkline = ft_strlen(stash);
	line = ft_substr(stash, 0, real_brkline + 1);
	tmp = stash;
	stash = ft_substr(tmp, real_brkline + 1, ft_strlen(tmp));
	return (line);
}

// int	main(void)
// {
// 	char		*res;
// 	int			fd;

// 	// fd = open("./gnlTester/files/empty", O_RDONLY);
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
// 	return (0);
// }