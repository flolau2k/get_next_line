/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:25:27 by flauer            #+#    #+#             */
/*   Updated: 2023/04/17 15:21:01 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/// @brief clear static buffer and keep what was not returned.
/// @param buf pointer to state buffer
/// @param start index of the first byte that was not returned.
static void	handle_state_buffer(char *buf, size_t start)
{
	size_t	len;

	len = f_strlen(buf + start);
	ft_memmove(buf, buf + start, len);
	ft_bzero(buf + len, BUFFER_SIZE - len);
}

static char	*nl_from_state_buf(char *buf, int end)
{
	char	*result;
	size_t	rem_len;

	rem_len = 0;
	result = f_substr(buf, 0, end + 1);
	if (!result)
		return (NULL);
	handle_state_buffer(buf, end + 1);
	return (result);
}

static char	*nl_from_read_buf(char *result, char *buf)
{
	size_t	i;
	size_t	len;
	char	*res;

	i = 0;
	if (!result)
		return (NULL);
	len = f_strlen(result);
	while (i < len && result[i])
	{
		if (result[i] == '\n')
		{
			i++;
			break;
		}
		i++;
	}
	f_memcpy(buf, result + i, len - i);
	ft_bzero(buf + len - i, BUFFER_SIZE - (len - i));
	res = f_substr(result, 0 , i);
	if (!res)
		return (NULL);
	free (result);
	result = NULL;
	return (res);
}

static int	check_buf(const char *buf)
{
	int	i;

	i = 0;
	if (!buf)
		return (-1);
	while(i < BUFFER_SIZE && buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static bool	read_recursive(int fd, char **result, size_t *result_size)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	bytes_read;
	ssize_t	check;
	
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	check = check_buf(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && *result_size == 0))
		return (false);
	else if (bytes_read == 0 || check >= 0)
	{
		*result = malloc(sizeof(**result) * (*result_size + bytes_read + 1));
		if (!*result)
			return (false);
		(*result)[*result_size + bytes_read] = '\0';
		if (bytes_read)
			f_memcpy(*result + *result_size, buffer, bytes_read);
		return true;
	}
	*result_size += bytes_read;
	if (!read_recursive(fd, result, result_size))
		return (false);
	size_t buffer_offset = *result_size - bytes_read;
	f_memcpy(*result + buffer_offset, buffer, bytes_read);
	*result_size = buffer_offset;
	return true;
}

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	size_t		result_size;
	size_t		i;
	char		*result;
	
	i = 0;
	result_size = 0;
	result = NULL;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (nl_from_state_buf(buf, i));
	result_size = i;
	if (!read_recursive(fd, &result, &result_size))
	{
		ft_bzero(buf, BUFFER_SIZE + 1);
		return (NULL);
	}
	if (!result)
		return (NULL);
	f_memcpy(result, buf, i);
	return (nl_from_read_buf(result, buf));
}
