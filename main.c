/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/13 15:50:49 by dreijans      ########   odam.nl         */
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
		error("./pipex: too few arguments", errno);//errno has nothing so maybe different function?
	args = parse_args(argv);
	parse_path(envp, args);
	check_access1(args, argv);
	check_access2(args, argv);
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
//figure out correct error message for main.c:24
//full path as command input handling scalable to number of argv
//what happens if executable cant be found
//check acces1/2 check command absolute path->execute if not (path not found)
// what if environment null? not crashing!!!????
//check if path is unset!
//check if environment is unset
