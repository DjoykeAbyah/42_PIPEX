/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 12:47:14 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	int		pid1;
	int		pid2;
	int		pipe_fd[2];
	int		fd[2];

	if (argc != 5)
		ft_printf("too few arguments");
	args = parse_args(argv);
	parse_path(envp, args);
	check_access1(args);
	check_access2(args);
	if (pipe(pipe_fd) == -1)
		return (1);
	pid1 = fork();
	pid2 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		close(pipe_fd[READ]);
		fd[0] = open("file1", O_RDONLY);
		if (fd[0] == -1)
			return (3);
		dup2(fd[0], STDIN_FILENO);
		dup2(pipe_fd[WRITE], STDOUT_FILENO);
		close(fd[0]);
		close(pipe_fd[WRITE]);
		if (execve(args->executable, args->first_command, envp) == -1)
			return (4);
	}
	if (pid2 == 0)
	{
		close(pipe_fd[WRITE]);
		fd[1] = open("file2", O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd[1] == 0)
			return (5);
		dup2(pipe_fd[READ], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(pipe_fd[READ]);
		close(fd[1]);
		if (execve(args->executable2, args->second_command, envp) == -1)
			return (6);
	}
}

//improve error handling
//create process!
//use exit instead of return?

//what happens if someone gives the full path?
// if file ./command the error needs to be specific
//zorg dat er iets gebeurd als de executable er niet is check bash error 
//No such file or directory// bash: /usr/bin/me: No such file or directory
