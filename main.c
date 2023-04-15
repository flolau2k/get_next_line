/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:05:54 by flauer            #+#    #+#             */
/*   Updated: 2023/04/15 18:01:55 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	printf("Buffer size: %d\n", BUFFER_SIZE);

	int file = open("/home/florian/42/get_next_line_test/test2.txt", O_RDONLY);

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