/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:26:53 by flauer            #+#    #+#             */
/*   Updated: 2023/04/15 16:17:06 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*f_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*s1;
	char	*s2;

	if (dst == NULL && src == NULL)
		return (dst);
	i = 0;
	s1 = dst;
	s2 = (char *) src;
	while (i < n)
	{
		s1[i] = s2[i];
		i++;
	}
	return (dst);
}

void	ft_bzero(const void *buf, size_t n)
{
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *) buf;
	i = 0;
	while (i < n)
	{
		s[i] = 0;
		i++;
	}
}

size_t	f_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;

	i = 0;
	if (dstsize == 0)
		return (f_strlen(src));
	while (i < (dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (f_strlen(src));
}

size_t	f_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret])
		ret++;
	return (ret);
}
