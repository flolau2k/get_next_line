/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_stack.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 21:25:27 by flauer            #+#    #+#             */
/*   Updated: 2023/04/14 21:50:18 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_stack.h"

char *read_file_recursive(int fd, size_t *result_size)
{
	char buffer[BUFFER_SIZE];
	ssize_t bytes_read = read(fd, buffer, BUFFER_SIZE);

	if (bytes_read <= 0) {
		// Base case: end of file reached or error occurred
		// Allocate the result buffer
		char *result = malloc(*result_size + 1);
		result[*result_size] = '\0';
		return result;
	} else {
		// Recursive case: read more data
		// Increase the result size by the number of bytes read
		*result_size += bytes_read;

		// Call the function recursively
		char *result = read_file_recursive(fd, result_size);

		// Calculate the correct offset for the current buffer
		size_t buffer_offset = *result_size - bytes_read;

		// Copy the current buffer into the result buffer at the correct offset
		memcpy(result + buffer_offset, buffer, bytes_read);

		*result_size = buffer_offset;

		return result;
	}
}

char *read_file(int fd)
{
	static char	fd_state_buf[BUFFER_SIZE + 1];
	size_t		result_size = 0;
	size_t		i;
	
	i = 0;
	while (fd_state_buf[i] && fd_state_buf[i] != '\n')
		i++;
	if (fd_state_buf[i] == '\n')
		return (nl_from_state_buf(&fd_state_buf, i));
	else
		return (read_recursive(fd, &fd_state_buf, i));


	return read_file_recursive(fd, &result_size);
}
