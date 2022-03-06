/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 19:38:08 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 17:22:53 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_closepipes(t_arg *arg, int current)
{
	int	i;

	i = 0;
	while (i < arg[0].size)
	{
		if (i != current - 1)
			close(arg[i].fd[0]);
		if (i != current)
			close(arg[i].fd[1]);
		i ++;
	}
}

void	ft_stdread(int fd, char *lim)
{
	char	*line;

	while (get_next_line(&line))
	{
		if (ft_strncmp(lim, line, ft_strlen(lim) + 1) == 0)
		{
			free (line);
			close(fd);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
	}
}

void	ft_bonus(char *lim, t_arg *arg)
{
	arg[0].pid = ft_fork();
	if (arg[0].pid == 0)
	{
		ft_closepipes(arg, 0);
		ft_stdread(arg[0].fd[1], lim);
	}
	else
		waitpid (arg[0].pid, 0, 0);
}

void	ft_initarg(t_arg **arg, int size)
{
	int	i;

	i = 0;
	*arg = malloc (sizeof(t_arg) * size);
	if (!(*arg))
		exit(1);
	while (i < size)
	{
		ft_pipe((*arg)[i].fd);
		(*arg)[i].size = size;
		i ++;
	}
}

int	ft_check_heredoc(int argc, char **argv, int *out, t_arg **arg)
{
	char	*name;

	if (ft_strncmp(argv[1], "here_doc", 9) == 0)
	{
		*out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0664);
		if (*out < 0)
		{
			name = ft_strdup(argv[argc - 1]);
			ft_perror(&name, 1);
		}
		ft_initarg(arg, argc - 3);
		ft_bonus(argv[2], *arg);
		return (2);
	}
	return (1);
}
