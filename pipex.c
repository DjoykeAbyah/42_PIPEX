/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:54:14 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 18:36:37 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(int *fd, int *pipe_fd, t_pipex args, char **envp)
{
	close(pipe_fd[READ]);
	fd[0] = open("file1", O_RDONLY);//replace by argv[1] //if not exists open failed
	if (fd[0] == -1)
		error("fd", errno);
	dup2(fd[0], STDIN_FILENO);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(fd[0]);
	close(pipe_fd[WRITE]);
	if (access(args.executable, X_OK) != 0)
		error("path", errno);
	if (execve(args.executable, args.first_command, envp) == -1)
		exit(EXIT_FAILURE);
}

void	child_2(int *fd, int *pipe_fd, t_pipex args, char **envp)
{
	close(pipe_fd[WRITE]);
	fd[1] = open("file2", O_CREAT | O_WRONLY | O_TRUNC, 0644);//replace by argv[4] //if not exists open failed
	if (fd[1] == 0)
		error("fd", errno);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(pipe_fd[READ]);
	close(fd[1]);
	if (access(args.executable, X_OK) != 0)
		error("path", errno);
	if (execve(args.executable2, args.second_command, envp) == -1)
		exit(EXIT_FAILURE);
}
//bash-3.2$ <file--1 cat | wc -l> file2
//bash: file--1: No such file or directory
// try recreating this