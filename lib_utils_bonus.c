/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utls_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:41:39 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 16:42:33 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		if (((unsigned char *)s1)[i] == '\0' || ((unsigned char *)s2)[i] == '\0'
			|| ((unsigned char *)s1)[i] != ((unsigned char *)s2)[i])
			return ((int)(((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]));
		i ++;
		n --;
	}
	return (0);
}
