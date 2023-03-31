/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:36:28 by florian           #+#    #+#             */
/*   Updated: 2023/03/31 15:17:57 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	//static int	line = 0;
	char		*buf;
	char		c;
	int			i;

	buf = malloc(sizeof(char) * 80);
	i = 0;
	read(fd, &c, 1);
	while (c && c != '\n')
	{
		buf[i++] = c;
		read(fd, &c, 1);
	}
	buf[i] = '\n';
	return (buf);
}
