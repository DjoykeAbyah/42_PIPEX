/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:54:14 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/14 14:21:23 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* first child process */
void	child_1(int *fd, int *pipe_fd, t_pipex *args, char **envp)
{
	char	*executable;

	close(pipe_fd[READ]);
	fd[0] = open(args->input_file, O_RDONLY);
	if (fd[0] == -1)
		error(args->input_file, errno);
	dup2(fd[0], STDIN_FILENO);
	dup2(pipe_fd[WRITE], STDOUT_FILENO);
	close(fd[0]);
	close(pipe_fd[WRITE]);
	executable = check_access(args, args->first_command[0]);
	if (execve(executable, args->first_command, envp) == -1)
		error("execve_1", errno);
}

/* second child process */
void	child_2(int *fd, int *pipe_fd, t_pipex *args, char **envp)
{
	char	*executable;

	close(pipe_fd[WRITE]);
	fd[1] = open(args->output_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd[1] == 0)
		error(args->output_file, errno);
	dup2(pipe_fd[READ], STDIN_FILENO);
	dup2(fd[1], STDOUT_FILENO);
	close(pipe_fd[READ]);
	close(fd[1]);
	executable = check_access(args, args->second_command[0]);
	if (execve(executable, args->second_command, envp) == -1)
		error("execve_2", errno);
}

/* checks exit status, only needs it for the second child because 
everything before the pipe needs no error code everything after needs it
wait is called for child process 1 because i dont need that staus to exit*/
void	status_check(int pid2)
{
	int	status;

	waitpid(pid2, &status, 0);
	wait(NULL);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}
