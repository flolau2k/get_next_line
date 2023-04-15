/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:25:27 by flauer            #+#    #+#             */
/*   Updated: 2023/04/15 19:47:03 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*nl_from_state_buf(char *buf, int end)
{
	char	*result;
	size_t	rem_len;

	rem_len = 0;
	result = malloc(sizeof(*buf) * (end + 1));
	if (!result)
		return (NULL);
	rem_len = f_strlen(buf) - (end);
	f_strlcpy(result, buf, end + 1);
	f_memcpy(buf, buf + end, rem_len);
	ft_bzero(buf + rem_len, end);
	return (result);
}

static char	*nl_from_read_buf(char *result, char *buf, int end)
{
	size_t	rem_len;
	char	*res;

	rem_len = 0;
	rem_len = f_strlen(result) - (end);
	f_memcpy(buf, result + end, rem_len);
	ft_bzero(buf + rem_len, end);
	res = malloc(sizeof(*res) * (end + 1));
	f_strlcpy(res, result, end + 1);
	free (result);
	result = NULL;
	return (res);
}

static int	check_buf(const char *buf)
{
	size_t	i;
	size_t	len;

	i = 0;
	if (!buf)
		return (-1);
	len = f_strlen(buf);
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
	char	buffer[BUFFER_SIZE] = "";
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
	static char	buf[BUFFER_SIZE];
	size_t		result_size;
	size_t		i;
	char		*result;
	
	i = 0;
	result_size = 0;
	result = NULL;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		return (nl_from_state_buf(buf, i + 1));
	result_size = i;
	result = read_recursive(fd, &result_size);
	if (!result)
		return (NULL);
	f_memcpy(result, buf, i);
	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (result[i] == '\n')
		return (nl_from_read_buf(result, buf, i + 1));
	return (nl_from_read_buf(result, buf, i));
}
