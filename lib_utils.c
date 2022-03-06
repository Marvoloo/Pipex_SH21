/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:18:42 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 15:25:59 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *)malloc(sizeof(char) * ((ft_strlen(s1) + 1)));
	if (s2 == 0)
		return (0);
	ft_strlcpy(s2, s1, ft_strlen(s1) + 1);
	return (s2);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dst_len;

	i = 0;
	dst_len = ft_strlen(dst);
	if (dstsize == 0 || dstsize <= dst_len)
		return (dstsize + ft_strlen(src));
	while (i < dstsize - dst_len - 1 && src[i] != '\0')
	{
		dst[i + dst_len] = src[i];
		i ++;
	}
	dst[i + dst_len] = '\0';
	return (ft_strlen(src) + dst_len);
}

size_t	ft_strlen(const char *c)
{
	size_t	len;

	len = 0;
	while (*c != '\0')
	{
		c ++;
		len ++;
	}
	return (len);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (needle[j] == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		while (haystack[i + j] == needle[j]
			&& haystack[i + j] != '\0' && len - j > 0)
		{
			j ++;
			if (needle[j] == '\0')
				return ((char *)(haystack + i));
		}
		j = 0;
		i ++;
		len --;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;

	if (s1 == 0)
		return (0);
	str = (char *) malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (str == 0)
		return (0);
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	return (str);
}
