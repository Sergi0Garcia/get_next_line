/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:54:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/20 13:57:05 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

	size_t	ft_strlen(const char *s)
	{
		size_t	i;

		i = 0;
		while (s && s[i])
		{
			i++;
		}
		return (i);
	}

void clean_buffer(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{
		buff[i] = 0;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	size_t	rlen;
	char	*str;

	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
	rlen = len;
	if (len > strlen)
		rlen = strlen;
	str = (char *)malloc(sizeof(char) * (rlen + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < strlen && s[start + i] && i < rlen)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}
