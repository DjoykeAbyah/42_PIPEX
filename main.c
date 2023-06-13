/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/13 21:19:19 by dreijans      ########   odam.nl         */
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
	int		fd[2];

	// atexit(&leaks);
	if (argc != 5)
		error("./pipex: too few or little arguments", errno);
	args = parse_args(argv);
	parse_path(envp, args);
	if (pipe(pipe_fd) == -1)
		error("pipe", errno);
	pid[0] = fork();
	if (pid[0] < 0)
		error("fork", errno);
	if (pid[0] == 0)
		child_1(fd, pipe_fd, args, envp);
	pid[1] = fork();
	if (pid[1] < 0)
		error("fork", errno);
	if (pid[1] == 0)
		child_2(fd, pipe_fd, args, envp);
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	status_check(pid[0], pid[1]);
}

//do leak check
//check inner workings of status check
//figure out correct error message for main.c:24
//errno has nothing so maybe different function?
//what happens if executable cant be found
//check error message for permissions
//check bash error messages below

/*
bash: no job control in this shell
bash-3.2$ <file1 bin/cat | bin/cat > file2
bash: bin/cat: No such file or directory
bash: bin/cat: No such file or directory
bash-3.2$ exit
exit

PIPEX_HOME on  master [!?] took 34.3s 
➜ ./pipex file1 bin/cat bin/cat file2
path: Bad address
path: Bad address
*/

//bash-3.2$ <file--1 cat | wc -l> file2
//bash: file--1: No such file or directory
//pipex.c:41 geeft bad address //bash: cat: No such file or directory
// try recreating this

/* prints arrays, for testing */
// void	print_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		ft_printf("%s\n", array[i]);
// 		i++;
// 	}	
// }

	// print_array(args->path);
	// printf("%s\n",args->executable);
	// printf("%s\n",args->executable2);
	// print_array(args->first_command);
	// print_array(args->second_command);