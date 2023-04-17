/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:39:52 by flauer            #+#    #+#             */
/*   Updated: 2023/04/17 15:46:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	f_strlen(const char *s)
{
	size_t	ret;

	ret = 0;
	while (s[ret])
		ret++;
	return (ret);
}

size_t	ft_strncpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (f_strlen(src));
	while (i < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	return (f_strlen(src));
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

char	*f_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	strlen;

	strlen = f_strlen(s);
	if (strlen < start)
	{
		ret = malloc(1 * sizeof(char));
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

void	*f_calloc(size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(size);
	if (!ret)
		return (NULL);
	while (i < size)
	{
		ret[i] = 0;
		i++;
	}
	return ((void *) ret);
}
