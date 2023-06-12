/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 15:34:39 by dreijans      ########   odam.nl         */
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
		error("too few arguments", errno);//too few arguments?
	args = parse_args(argv);
	parse_path(envp, args);
	check_access1(args);
	check_access2(args);
	if (pipe(pipe_fd) == -1)
		error("pipe", errno);
	pid1 = fork();
	if (pid1 < 0)
		error("fork", errno);
	if (pid1 == 0)
		child_1(fd, pipe_fd, *args, envp);
	pid2 = fork();
	if (pid2 < 0)
		error("fork", errno);
	if (pid2 == 0)
		child_2(fd, pipe_fd, *args, envp);
}

//improve error handling
//what happens if someone gives the full path?
// if file ./command the error needs to be specific
//zorg dat er iets gebeurd als de executable er niet is check bash error 