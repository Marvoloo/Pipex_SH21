/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:08:25 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 17:24:06 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_read(char *argv, char **envp, t_arg *arg, int i)
{
	char	*path;
	char	**cmds;

	arg[i].pid = ft_fork();
	if (arg[i].pid == 0)
	{	
		ft_closepipes(arg, i);
		dup2(arg[i -1].fd[0], 0);
		dup2(arg[i].fd[1], 1);
		cmds = ft_check_cmds(ft_split(argv, ' '));
		path = ft_getpath(cmds, envp, 127, arg);
		ft_process(cmds, path, envp, arg);
	}
}

int	ft_firstread(int in, char *argv, char **envp, t_arg *arg)
{
	char	*path;
	char	**cmds;

	if (in >= 0)
	{	
		arg[0].pid = ft_fork();
		if (arg[0].pid == 0)
		{	
			ft_closepipes(arg, 0);
			dup2(in, 0);
			dup2(arg[0].fd[1], 1);
			cmds = ft_check_cmds(ft_split(argv, ' '));
			path = ft_getpath(cmds, envp, 127, arg);
			ft_process(cmds, path, envp, arg);
		}
		return (0);
	}
	return (1);
}

void	ft_write(int out, char *argv, char **envp, t_arg *arg)
{
	char	*path;
	char	**cmds;

	arg[arg[0].size - 1].pid = ft_fork();
	if (arg[arg[0].size - 1].pid == 0)
	{	
		ft_closepipes(arg, arg[0].size - 1);
		close(arg[arg[0].size - 1].fd[1]);
		dup2(out, 1);
		dup2(arg[arg[0].size - 2].fd[0], 0);
		cmds = ft_check_cmds(ft_split(argv, ' '));
		path = ft_getpath(cmds, envp, 127, arg);
		ft_process(cmds, path, envp, arg);
	}
}

void	ft_waitallchild(t_arg *arg, int *flag, int a)
{
	int	i;

	i = 0;
	*flag = 0;
	while (i < arg[0].size)
	{	
		if (a == 1 && i == 0)
			i ++;
		else
		{
			if (i != arg[0].size - 1)
				waitpid(arg[i].pid, 0, 0);
			else
				waitpid(arg[i].pid, flag, 0);
			i ++;
		}
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		in;
	int		out;
	int		i;
	int		flag;
	t_arg	*arg;

	if (argc < 5)
		exit(1);
	i = ft_check_heredoc(argc, argv, &out, &arg);
	if (i == 1)
	{
		ft_openfile(&in, 0, argv[1]);
		ft_openfile(&out, 1, argv[argc - 1]);
		ft_initarg(&arg, argc - 3);
		flag = ft_firstread(in, argv[2], envp, arg);
		i ++;
	}
	while (++ i < argc - 2)
		ft_read(argv[i], envp, arg, i - 2);
	ft_write(out, argv[argc - 2], envp, arg);
	ft_closepipes(arg, -228);
	ft_waitallchild(arg, &i, flag);
	free(arg);
	return (WEXITSTATUS(i));
}
