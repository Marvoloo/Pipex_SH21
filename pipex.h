/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fdonetta <fdonetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 20:14:29 by fdonetta          #+#    #+#             */
/*   Updated: 2022/03/06 16:42:58 by fdonetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct s_arg {
	int		pid;
	int		fd[2];
	int		size;
}	t_arg;

int		ft_fork(void);
void	ft_free(char **array);
void	ft_pipe(int fd[2]);
void	ft_perror(char **name, int a);
void	ft_errmsg(char **name, char *str, int a);
void	ft_openfile(int *fd, int i, char *file);
void	ft_process(char **cmds, char *path, char **envp, t_arg *arg);
void	ft_initarg(t_arg **arg, int size);
char	*ft_getpath(char **cmds, char **envp, int errno, t_arg *arg);
char	**ft_check_cmds(char **cmds);
char	**ft_join(char **str, int a, int b, int len);
int		ft_remdqoutes(char **str, int *flag);
void	ft_closepipes(t_arg *arg, int current);
int		ft_check_heredoc(int argc, char **argv, int *out, t_arg **arg);

size_t	ft_strlen(const char *c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size);
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s1);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

#endif