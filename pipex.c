/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 16:05:08 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 16:43:55 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_read(int in, char *argv, char **envp, t_arg *pids)
{
	char	*path;
	char	**cmds;

	if (in >= 0)
	{	
		pids[0].pid = ft_fork();
		if (pids[0].pid == 0)
		{	
			close(pids[0].fd[0]);
			dup2(in, 0);
			dup2(pids[0].fd[1], 1);
			cmds = ft_check_cmds(ft_split(argv, ' '));
			path = ft_getpath(cmds, envp, 127, pids);
			ft_process(cmds, path, envp, pids);
		}
	}
}

void	ft_write(int out, char *argv, char **envp, t_arg *pids)
{
	char	*path;
	char	**cmds;

	pids[1].pid = ft_fork();
	if (pids[1].pid == 0)
	{	
		close(pids[0].fd[1]);
		dup2(out, 1);
		dup2(pids[0].fd[0], 0);
		cmds = ft_check_cmds(ft_split(argv, ' '));
		path = ft_getpath(cmds, envp, 127, pids);
		ft_process(cmds, path, envp, pids);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		in;
	int		out;
	t_arg	*pids;
	int		flag;

	if (argc != 5)
		exit(1);
	ft_openfile(&in, 0, argv[1]);
	ft_openfile(&out, 1, argv[4]);
	pids = (t_arg *) malloc (sizeof(t_arg) * 2);
	if (!pids)
		exit(1);
	ft_pipe(pids[0].fd);
	ft_read(in, argv[2], envp, pids);
	ft_write(out, argv[3], envp, pids);
	close(pids[0].fd[0]);
	close(pids[0].fd[1]);
	if (in >= 0)
		waitpid(pids[0].pid, 0, 0);
	waitpid(pids[1].pid, &flag, 0);
	free(pids);
	return (WEXITSTATUS(flag));
}
