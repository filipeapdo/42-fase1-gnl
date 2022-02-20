/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:53:33 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/20 11:12:08 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ❯ gcc -Wall -Wextra -Werror -ggdb3 get_next_line.h get_next_line_utils.c get_next_line.c test.c
// ❯ time valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file="valgrind.log" ./a.out > a.log   >>>   4.56s user 0.01s system 99% cpu 4.570 total
// ❯ time valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file="valgrind.log" ./a.out > a.log   >>>   4.58s user 0.05s system 99% cpu 4.627 total

char	*flp_new_chunck(char *chunck)
{
	int		i;
	int		j;
	char	*s_new_chunck;

	i = 0;
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	if (*(chunck + i) == '\0')
	{
		free(chunck);
		return (NULL);
	}
	s_new_chunck = (char *)malloc(sizeof(char) * (ft_strlen(chunck) - i + 1));
	if (!s_new_chunck)
		return (NULL);
	i++;
	j = 0;
	while (*(chunck + i))
		*(s_new_chunck + j++) = *(chunck + i++);
	*(s_new_chunck + j) = '\0';
	free(chunck);
	return (s_new_chunck);
}

char	*flp_get_line(char *chunck)
{
	int		i;
	char	*s_line;

	i = 0;
	if (*(chunck + i) == '\0')
		return (NULL);
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	s_line = (char *)malloc(sizeof(char) * (i + 2));
	if (!s_line)
		return (NULL);
	i = 0;
	while (*(chunck + i) && *(chunck + i) != '\n')
	{
		*(s_line + i) = *(chunck + i);
		i++;
	}
	if (*(chunck + i) == '\n')
	{
		*(s_line + i) = *(chunck + i);
		i++;
	}
	*(s_line + i) = '\0';
	return (s_line);
}

int	flp_check_nl(char *chunck)
{
	int		i;
	int		nl;

	i = 0;
	nl = 0;
	while (*(chunck + i))
		if (*(chunck + i++) == '\n')
			nl = 1;
	return (nl);
}

char	*flp_read_chunck(int fd, char *chunck)
{
	int		nl;
	int		bytes_read;
	char	*s_buff;

	s_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s_buff)
		return (NULL);
	nl = 0;
	bytes_read = 1;
	while (nl == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, s_buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(s_buff);
			return (NULL);
		}
		*(s_buff + bytes_read) = '\0';
		chunck = flp_gnljoin(chunck, s_buff);
		nl = flp_check_nl(chunck);
	}
	free(s_buff);
	return (chunck);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*chunck;

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	chunck = flp_read_chunck(fd, chunck);
	if (!chunck)
		return (NULL);
	line = flp_get_line(chunck);
	chunck = flp_new_chunck(chunck);
	return (line);
}
