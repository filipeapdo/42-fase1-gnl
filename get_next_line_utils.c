/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:59:18 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/20 12:28:30 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*flp_gnljoin(char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*s_join;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		*s1 = '\0';
	}
	if (!s1 || !s2)
		return (NULL);
	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s_join)
		return (NULL);
	i = 0;
	j = 0;
	while (*(s1 + i))
		*(s_join + j++) = *(s1 + i++);
	i = 0;
	while (*(s2 + i))
		*(s_join + j++) = *(s2 + i++);
	*(s_join + j) = '\0';
	free(s1);
	return (s_join);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	i;

	i = 0;
	if (dstsize > 0)
	{
		while (*(src + i) && dstsize-- > 1)
		{
			*(dst + i) = *(src + i);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (ft_strlen(src));
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
