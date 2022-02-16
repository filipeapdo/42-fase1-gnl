/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 07:53:33 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/15 21:45:26 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "get_next_line.h"

char	*flp_gnljoin(char *s_old, const char *s_new)
{
	char	*s_gnljoin;

	s_gnljoin = ft_strjoin(s_old, s_new);
	free(s_old);
	return (s_gnljoin);
}

char	*flp_new_chunck(char *chunck)
{
	int		i;
	char	*s_new_chunck;

	i = 0;
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	// printf("5. i = %d\n", i);
	
	if (*(chunck + i) == '\0')
	{
		free(chunck);
		return (NULL);
	}
	
	s_new_chunck = (char *)malloc(sizeof(char) * (ft_strlen(chunck) - i + 1));
	if (!s_new_chunck)
		return (NULL);
	
	ft_strlcpy(s_new_chunck, (chunck + i + 1), (ft_strlen(chunck) - i + 1));
	free(chunck);
	return (s_new_chunck);
}

char	*flp_get_line(char *chunck)
{
	int		i;
	char	*s_line;

	i = 0;
	if (*chunck == '\0')
		return (NULL);
	
	while (*(chunck + i) && *(chunck + i) != '\n')
		i++;
	// printf("3. i = %d\n", i);
	
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

char	*flp_read_chunck(int fd, char *chunck)
{
	int		nl;
	int		bytes_read;
	int		i;
	char	*s_buff;

	s_buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!s_buff)
		return (NULL);
	nl = 0;
	bytes_read = 1;
	while (nl == 0 && bytes_read != 0)
	{
		// printf("1.1 flp_get_line_chunck_br : %s$\n", chunck);
		bytes_read = read(fd, s_buff, BUFFER_SIZE);
		// printf("1.2. flp_get_line_bytes_read : %d#\n", bytes_read);
		if (bytes_read == -1)
		{
			free(s_buff);
			return (NULL);
		}
		*(s_buff + bytes_read) = '\0';
		chunck = flp_gnljoin(chunck, s_buff);
		i = 0;
		while (*(chunck + i))
		{
			if (*(chunck + i) == '\n')
				nl = 1;
			i++;
		}
		// printf("1.3 flp_get_line_chunck_ar : %s$\n", chunck);
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
	// printf("2. chunck : %s$\n", chunck);
	if (!chunck)
		return (NULL);
	
	line = flp_get_line(chunck);
	// printf("4. line : %s$\n", line);
	
	chunck = flp_new_chunck(chunck);
	// printf("6. new_chunck : %s$\n", chunck);
	return (line);
}
