/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remqoutes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:20:06 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/05 19:25:25 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_newcpy(char **str, char c, int *pos, int start)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = (char *) malloc(sizeof(char) * (ft_strlen(*str) - 1));
	if (!tmp)
		return ;
	while ((*str)[i])
	{	
		if ((*str)[i] == c && (i - j) < 2 && i >= start)
			*pos = j;
		else
			tmp[j ++] = (*str)[i];
		i ++;
	}
	tmp[j] = '\0';
	free(*str);
	*str = tmp;
}

void	ft_mindgame(int i, char **str, char c)
{
	int		j;
	char	*newstr;

	j = 0;
	while ((*str)[i ++] == c)
		j ++;
	newstr = (char *) malloc(sizeof(char) * (ft_strlen(*str) - j));
	if (newstr == 0)
		return ;
	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == c)
		{	
			newstr[j ++] = (*str)[++ i];
			while ((*str)[i] == c)
				i ++;
		}
		else
			newstr[j ++] = (*str)[i ++];
	}
	newstr[j] = '\0';
	free(*str);
	*str = newstr;
}

int	ft_remqoutes(char **str, char c, int *a, int *flag)
{	
	int	i;

	i = *a;
	while ((*str)[++ (*a)])
	{
		if ((*str)[(*a)] == c)
		{
			ft_newcpy(str, c, a, i);
			return (0);
		}	
	}
	if (c == '\"')
		*flag = 1;
	if (c == 39)
		*flag = 2;
	return (1);
}

int	ft_remdqoutes(char **str, int *flag)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\' && (*str)[i + 1] == 39)
		{
			i += 2;
			ft_mindgame(i - 1, str, 39);
		}
		else if ((*str)[i] == '\"' && (*flag == 1 || *flag == -1))
			count = ft_remqoutes(str, '\"', &i, flag);
		else if ((*str)[i] == 39 && (*flag == 2 || *flag == -1))
			count = ft_remqoutes(str, 39, &i, flag);
		else
			i ++;
	}
	return (count);
}
