/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:06:18 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/20 12:28:28 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <stdlib.h>
# include <unistd.h>

// get_next_line
char	*get_next_line(int fd);
char	*flp_read_chunck(int fd, char *chunck);
char	*flp_get_line(char *chunck);
char	*flp_new_chunck(char *chunck);
int		flp_check_nl(char *chunck);

// get_next_line_utils
char	*flp_gnljoin(char *s1, const char *s2);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t	ft_strlen(const char *s);

#endif
