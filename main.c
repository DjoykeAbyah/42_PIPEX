/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/16 15:54:29 by dreijans      ########   odam.nl         */
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

//------------------------------------------------------------------------

// check for empty string // do i need to give the same error message?
// bash-3.2$ ./pipex file1 "" "" file2
// bash-3.2$ <file1 "" "" > file2
// bash: : command not found
// bash-3.2$ echo $?
// 127
// bash-3.2$ < file1 "" "" > file2
// bash: : command not found
// bash-3.2$ <file1 "" | "" > file2
// bash: : command not found
// bash: : command not found
// bash-3.2$ ./pipex file1 "" "" file2
// bash-3.2$ echo $?
// 0
// mine gives 0 is that okay?

//do i understand the exit message

// ------------------------------------------------------------------------
