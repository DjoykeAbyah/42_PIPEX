/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:54:14 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/13 19:25:51 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_1(int *fd, int *pipe_fd, t_pipex args, char **envp)
{
	close(pipe_fd[READ]);
	fd[0] = open(args.input_file, O_RDONLY);
	if (fd[0] == -1)
		error(args.input_file, errno);
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
	fd[1] = open(args.output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == 0)
		error(args.output_file, errno);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(pipe_fd[READ]);
	close(fd[1]);
	if (access(args.executable, X_OK) != 0)
		error("path", errno);
	if (execve(args.executable2, args.second_command, envp) == -1)
		exit(EXIT_FAILURE);
}
