/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/19 22:19:43 by dreijans      ########   odam.nl         */
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
//check bash error messages below
//do i understand the exit message

// cp /bin/cat .

// chmod -x ./cat

// ./pipex infile ls ./cat outfile

// ./pipex Makefile ./cat cat file2
// not this!!! please
// ./cat: no such file or directory
// cat: no such file or directory
// ./cat: no such file or directory
// cat: no such file or directory

// bash-3.2$ ./pipex file1 "" "" file2
// pipex: command not found
// pipex: command not found  gives errno error needs personalised?
// parse.c 51, 52??
// ------------------------------------------------------------------------
