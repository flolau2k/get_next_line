/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:05:54 by flauer            #+#    #+#             */
/*   Updated: 2023/04/12 13:05:40 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	printf("Buffer size: %d\n", BUFFER_SIZE);

	int file = open("/Users/flauer/Documents/get_next_line/empty_nl.txt", O_RDONLY);

	char *line;
	while (1)
	{
		line = get_next_line(file);
		if (line == NULL)
		{
			printf("Ende!");
			break;
		}
		printf("got this line: %s", line);
		fflush(stdout);
		sleep(1);
	}
	return (0);
}