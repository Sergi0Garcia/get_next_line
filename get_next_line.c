/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:29:06 by segarcia          #+#    #+#             */
/*   Updated: 2022/07/07 14:36:54 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		return (return_and_free(stash));
	str_len = ft_strlen(stash);
	next_stash = (char *)malloc(sizeof(char) * (str_len - brk_idx + 1));
	if (!next_stash)
		return (NULL);
	brk_idx++;
	while (stash[brk_idx])
		next_stash[i++] = stash[brk_idx++];
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
	if (!stash[i])
		return (NULL);
	brk_idx = get_nl_idx(stash);
	if (brk_idx == -1)
	{
		if (!ft_strlen(stash))
			return (NULL);
		brk_idx = ft_strlen(stash);
	}
	str = (char *)malloc(sizeof(char) * brk_idx + 2);
	if (!str)
		return (NULL);
	while (stash[i] && i < brk_idx)
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

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	read_nbr = BUFFER_SIZE;
	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (read_nbr > 0 && get_nl_idx(stash) == -1)
	{
		read_nbr = read(fd, buffer, BUFFER_SIZE);
		if (read_nbr == -1)
			return (return_and_free(buffer));
		buffer[read_nbr] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free(buffer);
	line = ft_get_line(stash);
	stash = ft_get_next_stash(stash);
	return (line);
}
