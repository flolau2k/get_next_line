/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:05:54 by flauer            #+#    #+#             */
/*   Updated: 2023/04/06 12:58:58 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	printf("Buffer size: %d\n", BUFFER_SIZE);

	//int file = open("/home/florian/42/get_next_line/test_input.txt", O_RDONLY);

	char *line;
	while (1)
	{
		//printf("getting new line...\n");
		line = get_next_line(-1);
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
