/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   joinarg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:33:57 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/05 19:35:02 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_catcmd(char **cmds, char *cmd)
{
	char	*str;
	char	*tmp;

	tmp = ft_strjoin(*cmds, " ");
	str = ft_strjoin(tmp, cmd);
	free(tmp);
	free(*cmds);
	*cmds = str;
}

char	**ft_join(char **str, int a, int b, int len)
{
	char	**ret;
	int		i;

	i = -1;
	while (str[len])
		len ++;
	ret = (char **) malloc (sizeof(char *) * (len - (b - a - 1)));
	if (!ret)
		return (str);
	while (++ i < a)
		ret[i] = ft_strdup(str[i]);
	ret[i] = ft_strdup(str[a]);
	while (++ a <= b)
		ft_catcmd(&ret[i], str[a]);
	i ++;
	while (str[a])
		ret[i ++] = ft_strdup(str[a ++]);
	ret[i] = 0;
	ft_free(str);
	return (ret);
}
