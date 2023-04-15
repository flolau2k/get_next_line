/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 15:05:54 by flauer            #+#    #+#             */
/*   Updated: 2023/04/15 16:16:06 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include <criterion/criterion.h>
#include <stdio.h>
#include <fcntl.h>
#if __linux__
# include <linux/limits.h>
#else
# include <limits.h>
#endif
#include <unistd.h>

char cwd[PATH_MAX];
int fd;
char *next_line;

void	setup(void)
{
	getcwd(cwd, PATH_MAX);
}
TestSuite(gnl_tester, .init=setup);

Test(gnl_tester, simple_test)
{
	strcat(cwd, "/test_input.txt");
	cr_log_info("opening file: %s\n", cwd);
	fd = open(cwd, O_RDONLY);
	char *next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "ksadjflksdj\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "as\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "dfs\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "daf\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "as\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "dfsasdf\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "\n"));
	next_line = get_next_line(fd);
	cr_assert(!strcmp(next_line, "DKJL\n"));
	next_line = get_next_line(fd);
	cr_assert(next_line == NULL);
	close(fd);
}

Test(gnl_tester, simple_test2)
{
	strcat(cwd, "/empty_file.txt");
	cr_log_info("opening file: %s\n", cwd);
	fd = open(cwd, O_RDONLY);
	close(fd);
	char *next_line = get_next_line(fd);
	cr_assert(next_line == NULL);
	next_line = get_next_line(-100);
	cr_assert(next_line == NULL);
	next_line = get_next_line(42);
	cr_assert(next_line == NULL);
	next_line = get_next_line(3);
	cr_assert(next_line == NULL);
	next_line = get_next_line(1025);
	cr_assert(next_line == NULL);
}

Test(gnl_tester, empty_file_test)
{
	strcat(cwd, "/empty_file.txt");
	cr_log_info("opening file: %s\n", cwd);
	fd = open(cwd, O_RDONLY);
	next_line = get_next_line(fd);
	cr_assert(next_line == NULL);
	close(fd);
}

Test(gnl_tester, nl)
{
	strcat(cwd, "/empty_nl.txt");
	cr_log_info("opening file: %s\n", cwd);
	fd = open(cwd, O_RDONLY);
	next_line = get_next_line(fd);
	cr_assert(next_line);
	cr_assert(!strcmp(next_line, "\n"));
	close(fd);
}

Test(gnl_tester, buffer_size)
{
	strcat(cwd, "/buf80.txt");
	cr_log_info("opening file: %s\n", cwd);
	fd = open(cwd, O_RDONLY);
	next_line = get_next_line(fd);
	cr_assert(next_line);
	cr_assert(!strcmp("laksjdflkjasdfjlkjasdlfjlkadsjflkjasdlkdfjlasdjfljalskdfjlajsdflkjalskddfjlasdfd\n", next_line));
}
