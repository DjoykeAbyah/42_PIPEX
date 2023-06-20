/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:54:14 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/20 18:14:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* first child process */
void	child_1(int *pipe_fd, t_pipex *args, char **envp, char **argv)
{
	char	*executable;
	int		fd1;

	close_check(pipe_fd[READ]);
	fd1 = open(args->input_file, O_RDONLY);
	if (fd1 == -1)
		error(args->input_file, errno);
	dup2(fd1, STDIN_FILENO);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close_check(fd1);
	close_check(pipe_fd[WRITE]);
	check_space_and_null(argv[2]);
	executable = check_access(envp, args, args->first_command[0]);
	if (access(executable, X_OK) == -1)
		error(executable, errno);
	if (execve(executable, args->first_command, envp) == -1)
		error(*args->first_command, errno);
}

/* second child process */
void	child_2(int *pipe_fd, t_pipex *args, char **envp, char **argv)
{
	char	*executable;
	int		fd2;

	close_check(pipe_fd[WRITE]);
	fd2 = open(args->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd2 == 0)
		error(args->output_file, errno);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(fd2, STDOUT_FILENO);
	close_check(pipe_fd[READ]);
	close_check(fd2);
	check_space_and_null(argv[3]);
	executable = check_access(envp, args, args->second_command[0]);
	if (access(executable, X_OK) == -1)
		error(executable, errno);
	if (execve(executable, args->second_command, envp) == -1)
		error(*args->second_command, errno);
}
