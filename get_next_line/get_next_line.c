/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:25:27 by flauer            #+#    #+#             */
/*   Updated: 2023/04/15 16:17:02 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*nl_from_state_buf(char *buf, int end)
{
	char	*result;
	size_t	rem_len;

	rem_len = 0;
	result = malloc(sizeof(*buf) * (end + 2));
	if (!result)
		return (NULL);
	rem_len = f_strlen(buf) - (end + 1);
	f_strlcpy(result, buf, end + 2);
	f_memcpy(buf, buf + end + 1, rem_len);
	ft_bzero(buf + rem_len, end + 1);
	return (result);
}

static int	check_buf(const char *buf)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = f_strlen(buf);
	if (!buf)
		return (-1);
	while(i < len && buf[i])
	{
		if (buf[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

static char *read_recursive(int fd, size_t *result_size)
{
	char	buffer[BUFFER_SIZE];
	char	*result;
	ssize_t	bytes_read;
	ssize_t	check;
	
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	check = check_buf(buffer);
	if (bytes_read < 0 || (bytes_read == 0 && *result_size == 0))
		return (NULL);
	else if (bytes_read == 0 || check)
	{
		// Base case: end of file reached or error occurred
		// Allocate the result buffer
		result = malloc(sizeof(*result) * (*result_size + bytes_read + 1));
		if (!result)
			return (NULL);
		result[*result_size + bytes_read] = '\0';
		if (bytes_read)
			f_memcpy(result + *result_size, buffer, bytes_read);
		return result;
	}
	else
	{
		// Recursive case: read more data
		// Increase the result size by the number of bytes read
		*result_size += bytes_read;

		// Call the function recursively
		result = read_recursive(fd, result_size);

		// Calculate the correct offset for the current buffer
		size_t buffer_offset = *result_size - bytes_read;

		// Copy the current buffer into the result buffer at the correct offset
		f_memcpy(result + buffer_offset, buffer, bytes_read);

		*result_size = buffer_offset;

		return result;
	}
}

char	*get_next_line(int fd)
{
	static char	*buf;
	size_t		result_size = 0;
	size_t		i;
	char		*result;
	
	i = 0;
	result = NULL;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	if (buf && buf[i] == '\n')
		return (nl_from_state_buf(buf, i));
	result_size = i;
	result = read_recursive(fd, &result_size);
	if (!result)
		return (NULL);
	f_memcpy(result, buf, i);
	if (buf)
		free(buf);
	buf = result;
	return (get_next_line(fd));
}
