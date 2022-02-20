/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fiaparec <fiaparec@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:59:18 by fiaparec          #+#    #+#             */
/*   Updated: 2022/02/18 17:52:02 by fiaparec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

//	BUFFER_SIZE = 1
// 		real    0m9.957s
// 		user    0m9.886s
// 		sys     0m0.070s
// char	*flp_gnljoin(char *s1, char const *s2)
// {
// 	char	*s_join;

// 	if (!s1 && !s2)
// 		return (NULL);
// 	if (!s1)
// 		return (ft_strdup(s2));
// 	if (!s2)
// 		return (ft_strdup(s1));
// 	s_join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!s_join)
// 		return (NULL);
// 	ft_strlcpy(s_join, s1, ft_strlen(s1) + 1);
// 	ft_strlcat(s_join, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
// 	free(s1);
// 	return (s_join);
// }

//	BUFFER_SIZE = 1
// 		real    0m5.491s
// 		user    0m5.441s
// 		sys     0m0.051s
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

char	*ft_strdup(const char *s)
{
	char	*s_dup;

	if (!s)
		return (NULL);
	s_dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!s_dup)
		return (NULL);
	ft_strlcpy(s_dup, s, ft_strlen(s) + 1);
	return (s_dup);
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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	int		i;
	size_t	len_src;
	size_t	len_dst;

	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize == 0)
		return (len_src);
	else if (len_dst >= dstsize)
		return (len_src + dstsize);
	else
	{
		while (*(src + i) && ((dstsize--) - len_dst) > 1)
		{
			*(dst + len_dst + i) = *(src + i);
			i++;
		}
		*(dst + len_dst + i) = '\0';
	}
	return (len_src + len_dst);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}
