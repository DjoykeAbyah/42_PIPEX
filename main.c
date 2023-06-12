/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 17:03:26 by dreijans      ########   odam.nl         */
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
		error("too few arguments", errno);
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

	// print_array(args->path);
	// printf("%s\n",args->executable);
	// printf("%s\n",args->executable2);
	// print_array(args->first_command);
	// print_array(args->second_command);