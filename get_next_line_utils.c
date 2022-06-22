/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: segarcia <segarcia@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 09:54:35 by segarcia          #+#    #+#             */
/*   Updated: 2022/06/22 13:12:03 by segarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	// printf("-%s-\n", s);
	while (s && s[i])
	{
		i++;
	}
	// printf("i: %i\n", (int)i);`
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

void clean_str(char *s, int len)
{
	int	i;

	i = 0;
	while (s[i] && i < len)
	{
		s[i] = 0;
		i++;
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
char	*ft_strjoin(char *s1, char *s2, int len)
{
	size_t	len1;
	size_t	len2;
	size_t	i;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen((char *)s1);
	len2 = (size_t)len;
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len1)
	{
		str[i] = s1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		str[i] = s2[i - len1];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	ft_copy(char *dest, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		// printf("%i\n", i);
		// printf("[%i] Dest: %c - Src %i\n", i, dest[i], src[i]);
		dest[i] = src[i];
		i++;
	}
}