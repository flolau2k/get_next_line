/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:36:28 by florian           #+#    #+#             */
/*   Updated: 2023/04/06 09:23:13 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	get_line_len(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE && buffer[i])
	{
		if (buffer[i] == '\n')
		{
			i++;
			break ;
		}
		i++;
	}
	return i;
}

char	*alloc_next_line(char *start, int len)
{
	char	*ret;
	int		i;

	i = 0;
	ret = malloc(sizeof(*start) * (len + 1));
	while (start[i] && i < len)
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = 0;
	return ret;
}

char	*get_next_line(int fd)
{
	static char	*buffer[FOPEN_MAX];
	static int	curr_line_len = 0;
	static int	next_line_len = 0;
	static int	*next_line = NULL;
	static int	nbytes_read = 0;

	// free next_line from last call.
	if (next_line)
	{
		free(next_line);
		next_line = NULL;
	}

	// make sure to return what is left in the buffer from last read call.
	if (nbytes_read)
	{
		next_line_len = get_line_len(buffer + curr_line_len);
		
	}

	// read from the buffer at max BUFFER_SIZE
	nbytes_read = read(fd, buffer, BUFFER_SIZE);

	// if nbytes_read is smaller or equal to zero nothing was read.
	if (nbytes_read <= 0)
		return NULL;
	// get length of next line until \n char.
	curr_line_len = get_line_len(buffer);

	// use the nbytes_read variable now as a counter how many bytes are still in the buffer
	// and were not yet returned.
	if (nbytes_read > curr_line_len)
		nbytes_read -= curr_line_len;

	next_line = alloc_next_line(buffer, curr_line_len);
	return (next_line);

}

