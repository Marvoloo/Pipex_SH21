/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findqoutes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:09:01 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/05 19:11:41 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_finddqoutes(char **str, char c, int *a, int *flag)
{	
	while ((*str)[++ (*a)])
	{
		if ((*str)[(*a)] == c)
		{
			(*a)++;
			return (0);
		}	
	}
	if (c == '\"')
		*flag = 1;
	if (c == 39)
		*flag = 2;
	return (1);
}

int	ft_findsecqoutes(char **str, int *flag)
{
	int	i;

	i = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\"' && (*flag == 1 || *flag == -1))
			return (1);
		else if ((*str)[i] == 39 && (*flag == 2 || *flag == -1))
			return (1);
		else
			i ++;
	}
	return (0);
}

int	ft_findqoutes(char **str, int *flag)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while ((*str)[i])
	{
		if ((*str)[i] == '\\')
		{
			i ++;
			while ((*str)[i] == 39)
				i ++;
		}
		else if ((*str)[i] == '\"' && (*flag == 1 || *flag == -1))
			count = ft_finddqoutes(str, '\"', &i, flag);
		else if ((*str)[i] == 39 && (*flag == 2 || *flag == -1))
			count = ft_finddqoutes(str, 39, &i, flag);
		else
			i ++;
	}
	return (count);
}

void	ft_startremdqoutes(char **cmds)
{
	int	i;
	int	flag;

	i = 0;
	flag = -1;
	while (cmds[i])
		ft_remdqoutes(&(cmds[i ++]), &flag);
}

char	**ft_check_cmds(char **cmds)
{
	int	i;
	int	a;
	int	flag;

	i = -1;
	a = -1;
	flag = -1;
	while (cmds[++ i])
	{		
		if (a == -1)
		{
			if (ft_findqoutes(&(cmds[i]), &flag))
				a = i;
		}
		else if (ft_findsecqoutes(&(cmds[i]), &flag))
		{
			cmds = ft_join(cmds, a, i, 0);
			i = a - 1;
			a = -1;
			flag = -1;
		}
	}
	ft_startremdqoutes(cmds);
	return (cmds);
}
