/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:53:33 by fiaparec          #+#    #+#             */
/*   Updated: 2022/05/25 21:19:15 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// ❯ gcc -Wall -Wextra -Werror -ggdb3 get_next_line.h get_next_line_utils.c get_next_line.c test.c
// ❯ time valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file="valgrind.log" ./a.out > a.log   >>>   4.53s user 0.07s system 99% cpu 4.596 total
// ❯ time valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -s --log-file="valgrind.log" ./a.out > a.log   >>>   4.56s user 0.03s system 99% cpu 4.593 total

char	*flp_new_chunck(char *chunck) // chunck = |2|2|2|2|3|\n|\0|
{
	size_t	i;
	char	*s_new_chunck;

	i = 0;
	while (*(chunck + i) && *(chunck + i) != '\n') // chunck = |2|2|2|2|3|\n|\0| >> 5
		i++;
	if (*(chunck + i) == '\0')
	{
		free(chunck);
		return (NULL);
	}
	s_new_chunck = (char *)malloc(sizeof(char) * (ft_strlen(chunck) - i + 1)); // 5 - 5 + 1 = 1
	if (!s_new_chunck)
		return (NULL);
	ft_strlcpy(s_new_chunck, (chunck + i + 1), (ft_strlen(chunck) - i + 1)); // |\0|
	free(chunck);
	return (s_new_chunck);
}

char	*flp_get_line(char *chunck) // chunck = |\n|3|3|3|\0|
{
	size_t	i;
	char	*s_line;

	i = 0;
	if (*(chunck + i) == '\0')
		return (NULL);
	while (*(chunck + i) && *(chunck + i) != '\n') // chunck = |\n|3|3|3|\0| >> i = 0
		i++;
	s_line = (char *)malloc(sizeof(char) * (i + 2)); // | | |[2]
	if (!s_line)
		return (NULL);
	if (*(chunck + i) == '\n')
		ft_strlcpy(s_line, chunck, (i + 2)); // |\n|\0|[2]
	if (*(chunck + i) == '\0')
		ft_strlcpy(s_line, chunck, (i + 1));
	return (s_line); // |\n|\0|[2]
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

char	*flp_read_chunck(int fd, char *chunck) // |\0| === NULL
{
	int		nl;
	int		bytes_read;
	char	*s_buff;

	s_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1)); // | | | | | | 
	if (!s_buff)
		return (NULL);
	nl = 0;
	bytes_read = 1;
	while (nl == 0 && bytes_read != 0)
	{
		bytes_read = read(fd, s_buff, BUFFER_SIZE); // s_buff = |\n|3|3|3|
		if (bytes_read == -1)
		{
			free(s_buff);
			return (NULL);
		}
		s_buff[bytes_read] = '\0'; // s_buff = |\n|3|3|3|\0|
		chunck = flp_gnljoin(chunck, s_buff); // chunck = |\n|3|3|3|\0|
		nl = flp_check_nl(chunck);
	}
	free(s_buff);
	return (chunck);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*chunck; // |\0| === NULL

	if (fd < 0 || fd > 256 || BUFFER_SIZE <= 0)
		return (NULL);
	chunck = flp_read_chunck(fd, chunck); // chunck = |\n|3|3|3|\0|
	if (!chunck)
		return (NULL);
	line = flp_get_line(chunck); s
	chunck = flp_new_chunck(chunck); // |3|3|3|\0|
	return (line);
}
