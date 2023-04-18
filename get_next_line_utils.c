/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 12:26:53 by flauer            #+#    #+#             */
/*   Updated: 2023/04/18 10:51:23 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned int	i;
	char			*c_dst;
	const char		*c_src;

	if (dst == NULL && src == NULL)
		return (NULL);
	if (len == 0 || (dst == src))
		return (dst);
	c_dst = dst;
	c_src = src;
	i = 0;
	if (c_src < c_dst)
	{
		while (len-- > 0)
			c_dst[len] = c_src[len];
	}
	else
	{
		while (i < len)
		{
			c_dst[i] = c_src[i];
			i++;
		}
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

char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	strlen;

	strlen = f_strlen(s);
	if (strlen < start)
	{
		ret = malloc(1 * sizeof(char));
		if (ret)
			ret[0] = 0;
		return (ret);
	}
	if (strlen - start < len)
		len = strlen - start;
	ret = malloc((len + 1) * sizeof(char));
	if (ret)
		f_strlcpy(ret, s + start, len + 1);
	return (ret);
}
