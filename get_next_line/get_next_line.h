/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flauer <flauer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/31 14:37:53 by flauer            #+#    #+#             */
/*   Updated: 2023/04/11 10:55:26 by flauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdio.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 80
# endif

char	*get_next_line(int fd);
size_t	f_strlcpy(char *dst, const char *src, size_t dstsize);
char	*f_substr(char const *s, unsigned int start, size_t len);
size_t	f_strlen(const char *s);
void	*f_calloc(size_t size);

#endif // !GET_NEXT_LINE_H
