/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 09:28:19 by flauer            #+#    #+#             */
/*   Updated: 2023/04/14 10:43:43 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// /// @brief allocate a new string, containing everything from start to end, 
// /// freeing the old string.
// /// @param buf pointer to state buffer
// /// @return 1 in case of success, 0 in case of malloc fail.
// static int	handle_state_buffer(char **buf, size_t start)
// {
// 	size_t	len;
// 	char	*temp;

// 	len = f_strlen(*buf + start);
// 	temp = malloc(sizeof(*temp) * (len + 1));
// 	if (!temp)
// 		return (0);
// 	f_strlcpy(temp, (*buf + start), (len + 1));
// 	free(*buf);
// 	*buf = NULL;
// 	*buf = temp;
// 	return (1);
// }

// /// @brief replacing buf with new newly allocated buffer, and read BUFFER_SIZE
// /// to the end of it.
// /// @param fd file descriptor to read from
// /// @param buf pointer to state buffer to read next chunk to.
// /// @return value of read() function, or -1 in case of malloc fail.
// static int	read_next_buffer_to_state(int fd, char **buf)
// {
// 	size_t	len;
// 	int		i;
// 	char	*newbuf;

// 	len = 0;
// 	newbuf = NULL;
// 	if (*buf)
// 		len = f_strlen(*buf);
// 	newbuf = f_calloc(sizeof(**buf) * (len + BUFFER_SIZE + 1));
// 	if (!newbuf)
// 		return (-1);
// 	if (*buf)
// 	{
// 		f_strlcpy(newbuf, *buf, (len + BUFFER_SIZE + 1));
// 		free(*buf);
// 		*buf = NULL;
// 	}
// 	*buf = newbuf;
// 	i = read(fd, *buf + len, BUFFER_SIZE);
// 	return (i);
// }

// /// @brief handle error: free buffer and return NULL.
// /// @param buf pointer to state buffer string
// /// @return NULL
// static char	*handle_error(char **buf)
// {
// 	free(*buf);
// 	*buf = NULL;
// 	return (NULL);
// }

// /// @brief allocate and return a string with the contents of the state buffer,
// /// after read returns 0 (nothing more to read). if the state buffer is empty,
// /// return NULL. Also free the state buffer and set to 0.
// /// @param buf pointer to state buffer
// /// @return allocated return string.
// static char	*handle_empty_read(char **buf)
// {
// 	char	*ret;

// 	ret = NULL;
// 	if (f_strlen(*buf) == 0)
// 	{
// 		free(*buf);
// 		return (*buf = NULL);
// 	}
// 	ret = malloc(sizeof(**buf) * (f_strlen(*buf) + 1));
// 	if (!ret)
// 		return (NULL);
// 	f_strlcpy(ret, *buf, f_strlen(*buf) + 1);
// 	free(*buf);
// 	*buf = NULL;
// 	return (ret);
// }

// /// @brief get the next line from the given file descriptor. 
// /// @param fd file descriptor
// /// @return next line, or NULL if error or nothing more to read.
// char	*get_next_line(int fd)
// {
// 	static char	*fd_state_buf;
// 	size_t		i;
// 	char		*ret;
// 	int			read_status;

// 	i = 0;
// 	ret = NULL;
// 	while (fd_state_buf && fd_state_buf[i])
// 	{
// 		if (fd_state_buf[i] == '\n')
// 		{
// 			ret = f_substr(fd_state_buf, 0, i + 1);
// 			if (!handle_state_buffer(&fd_state_buf, i + 1))
// 				return (NULL);
// 			return (ret);
// 		}
// 		i++;
// 	}
// 	read_status = read_next_buffer_to_state(fd, &fd_state_buf);
// 	if (read_status < 0)
// 		return (handle_error(&fd_state_buf));
// 	if (read_status == 0)
// 		return (handle_empty_read(&fd_state_buf));
// 	return (get_next_line(fd));
// }

// int	check_buf(char **buf)
// {
// 	size_t	i;

// 	i = 0;
// 	while (*buf && *buf[i])
// 	{
// 		if (*buf[i] == '\n')
// 			break ;
// 	}
// 	return (i);
// }

// expect state buf to contain \n char. malloc new string for return and 
// handle state buffer cleanup.
char	*nl_from_state_buf(char **fd_state_buf, size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(sizeof(*ret) * (size + 1));
	if (!ret)
		return (NULL);
	ret[size] = 0;
	while(i < size)
	{
		ret[i] = *fd_state_buf[i];
		i++;
	}
	i = 0;
	while (*fd_state_buf[size + i])
	{
		*fd_state_buf[i] = fd_state_buf[size + i];
		*fd_state_buf[size + i] = 0;
		i++;
	}
	*fd_state_buf[i] = 0;
	return (ret);
}


bool	handle_state_buffer(char **buf, char **tmp_buf, int n, int i)
{
	size_t	k;

	k = 0;
	
}

// read recursively into the stack until a newline char was read.
// return the status of read. 
/// @brief 
/// @param fd 
/// @param fd_state_buf 
/// @param size size of buffer that is already read
/// @return 
char	*read_recursive(int fd, char **fd_state_buf, size_t size)
{
	char	tmp_buf[BUFFER_SIZE + 1];
	size_t	i;
	size_t	n;
	char	*ret_buf;

	i = 0;
	ret_buf = NULL;
	n = read(fd, tmp_buf, BUFFER_SIZE);
	if (n < 0)
		return (NULL);
	while (i < n)
	{
		if (tmp_buf[i] == '\n')
		{
			ret_buf = malloc(sizeof(*tmp_buf) * size + i + 1);
			if (!ret_buf)
				return (NULL);
			ret_buf[size + i] = 0;
			// handle state buffer
			while (i >= 0)
			{
				ret_buf[size + i] = tmp_buf[i];
				i--;
				return (ret_buf);
			}
		}
		i++;
	}
	ret_buf = read_recursive(fd, fd_state_buf, size + BUFFER_SIZE);
	ft_strncpy(ret_buf + size, tmp_buf, BUFFER_SIZE); //TODO: protect!
	return (ret_buf);
}

char	*get_next_line(int fd)
{
	static char	fd_state_buf[BUFFER_SIZE + 1];
	char		*tmp_state_buf;
	size_t		i;

	i = 0;
	// if (fd < 0 || fd > FOPEN_MAX)
	// 	return (NULL);
	while (fd_state_buf[i] && fd_state_buf[i] != '\n')
		i++;
	if (fd_state_buf[i] == '\n')
		return (nl_from_state_buf(&fd_state_buf, i));
	else
		return (read_recursive(fd, &fd_state_buf, i));
}
