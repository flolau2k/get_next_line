/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:19 by flauer            #+#    #+#             */
/*   Updated: 2023/04/11 10:40:53 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/// @brief allocate a new string, containing everything from start to end, 
/// freeing the old string.
/// @param str buffer to handle
/// @return 
int	handle_state_buffer(char **buf, size_t start)
{
	size_t	len;
	char	*temp;

	len = f_strlen(*buf + start);
	temp = malloc(sizeof(*temp) * (len + 1));
	if (!temp)
		return (0);
	f_strlcpy(temp, (*buf + start), (len + 1));
	free(*buf);
	*buf = temp;
	return (1);
}

/// @brief replacing buf with new newly allocated buffer, and read BUFFER_SIZE
/// to the end of it.
/// @param fd file descriptor to read from
/// @param buf buffer to replace
/// @return value of read() function.
int	read_next_buffer_to_state(int fd, char **buf)
{
	size_t	len;
	int		i;
	char	*newbuf;

	len = 0;
	newbuf = NULL;
	if (*buf)
		len = f_strlen(*buf);
	newbuf = f_calloc(sizeof(**buf) * (len + BUFFER_SIZE + 1));
	if (!newbuf)
		return (-1);
	if (*buf)
	{
		f_strlcpy(newbuf, *buf, (len + BUFFER_SIZE + 1));
		free(*buf);
	}
	*buf = newbuf;
	i = read(fd, *buf + len, BUFFER_SIZE);
	return (i);
}

char	*handle_error(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (NULL);
}

char	*handle_empty_read(char **buf)
{
	char	*ret;

	ret = NULL;
	if (f_strlen(*buf) == 0)
	{
		free(*buf);
		return (*buf = NULL);
	}
	ret = malloc(sizeof(**buf) * (f_strlen(*buf) + 1));
	if (!ret)
		return (NULL);
	f_strlcpy(ret, *buf, f_strlen(*buf) + 1);
	free(*buf);
	*buf = NULL;
	return (ret);
}

/// @brief get the next line from the given file descriptor. 
/// @param fd 
/// @return 
char	*get_next_line(int fd)
{
	static char	*fd_state_buf[FOPEN_MAX];
	size_t		i;
	char		*ret;
	int			read_status;

	i = -1;
	ret = NULL;
	if (fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	while (fd_state_buf[fd] && fd_state_buf[fd][++i])
	{
		if (fd_state_buf[fd][i] == '\n')
		{
			ret = f_substr(fd_state_buf[fd], 0, i + 1);
			if (!handle_state_buffer(&fd_state_buf[fd], i + 1))
				return (NULL);
			return (ret);
		}
	}
	read_status = read_next_buffer_to_state(fd, &fd_state_buf[fd]);
	if (read_status < 0)
		return (handle_error(&fd_state_buf[fd]));
	if (read_status == 0)
		return (handle_empty_read(&fd_state_buf[fd]));
	return (get_next_line(fd));
}
