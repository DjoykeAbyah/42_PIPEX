/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/20 10:55:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// void	leaks(void)
// {
// 	pid_t pid = getpid();
// 	char *s;
// 	asprintf(&s, "leaks -q %d > %d", pid, pid);
// 	system(s);
// }

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	int		pid[2];
	int		pipe_fd[2];

	// atexit(&leaks);
	if (argc != 5)
		error("./pipex: incorrect arguments", errno);
	args = parse_args(argv);
	if (pipe(pipe_fd) == -1)
		error("pipe", errno);
	pid[0] = fork();
	if (pid[0] < 0)
		error("fork", errno);
	if (pid[0] == 0)
		child_1(pipe_fd, args, envp, argv);
	pid[1] = fork();
	if (pid[1] < 0)
		error("fork", errno);
	if (pid[1] == 0)
		child_2(pipe_fd, args, envp, argv);
	close_pipes(pipe_fd);
	status_check(pid[1]);
}

// -----------------------------------------------------------------------

//check inner workings of status check

// cp /bin/cat .

// chmod -x ./cat

// ./pipex infile ls ./cat outfile

// ./pipex Makefile ./cat cat file2
//

// ./cat: no such file or directory
// cat: no such file or directory
//mine
// ./cat: Permission denied

// parse.c 51, 52??
// ------------------------------------------------------------------------
