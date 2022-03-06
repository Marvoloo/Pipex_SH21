/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:27:51 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/05 19:28:44 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strjoin(char **str, char buf)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i])
		i ++;
	tmp = (char *) malloc (sizeof(char) * (i + 2));
	if (!tmp)
		return (0);
	i = 0;
	while ((*str)[i])
	{
		tmp[i] = (*str)[i];
		i ++;
	}	
	tmp[i] = buf;
	tmp[i + 1] = '\0';
	free(*str);
	(*str) = tmp;
	return (1);
}

int	get_next_line(char **line)
{
	char	buf;
	int		ret;

	*line = (char *) malloc (sizeof(char));
	if (!line)
		return (-1);
	(*line)[0] = '\0';
	ret = read (0, &buf, 1);
	while (ret > 0)
	{	
		if (buf == '\n')
			break ;
		if (!ft_strjoin(line, buf))
		{
			free(*line);
			return (-1);
		}
		ret = read (0, &buf, 1);
	}
	return (ret);
}
