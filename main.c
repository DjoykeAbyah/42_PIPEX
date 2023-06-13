/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/13 21:07:57 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void leaks(void)
{
	pid_t pid = getpid();
	char *s;
	asprintf(&s, "leaks -q %d > %d", pid, pid);
	system(s);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	int		pid[2];
	int		pipe_fd[2];
	int		fd[2];
	int		status;

	atexit(&leaks);
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
	waitpid(pid[0], NULL, 0);
	waitpid(pid[1], &status, 0);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

//everything before the pipe needs no error code everything after needs it
//why close in the main function?
//figure out correct error message for main.c:24
//errno has nothing so maybe different function?
//full path as command input handling scalable to number of argv
//what happens if executable cant be found
//check acces1/2 check command absolute path->execute if not (path not found)
// what if environment null? not crashing!!!????
//check if path is unset!
//check if environment is unset
//check error message for permissions 
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

// void	error(char *string, int error)
// {
// 	// write(1, "./pipex: ", 10);
// 	// write(1, string, ft_strlen(string));
// 	// write(1, strerror(errno), ft_strlen(strerror(errno)));
// 	perror(string);
// 	exit(error);
// }

/*function to reduce line count of access check but is not working properly*/
// char	*command_check(t_pipex *args)
// {
// 	char	*command;
// 	int		i;

// 	i = 0
// 	if (args->second_command[0][0] != '/')
// 		command = ft_strjoin("/", args->second_command[0]);
// 	else
// 		command = ft_strjoin("", args->second_command[0]);
// 	path = ft_strjoin(args->path[i], command);
// 	free(command);
// 	return (path);
// }

// void	fd_check(int fd1, int fd2)
// {
// }

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

/* checks if the path acces with access() for the first command.
zorg strjoin's freed  //&path[i] checks the character dumb dumb
//need to make it for the seconds command? */
// void	check_access1(t_pipex *args, char **argv)
// {
// 	char	*path;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	if (access(argv[2], F_OK) == 0)
// 		args->executable = argv[2];
// 	while (args->path[i] != NULL)
// 	{
// 		command = ft_strjoin("/", args->first_command[0]);
// 		path = ft_strjoin(args->path[i], command);
// 		free(command);
// 		if (access(path, F_OK) == 0)
// 		{
// 			args->executable = path;
// 			return ;
// 		}
// 		free(path);
// 		i++;
// 	}
// }

// /* checks if the path acces with access() for the first command.
// zorg strjoin's freed  //&path[i] checks the character dumb dumb
// //need to make it for the seconds command? */
// void	check_access2(t_pipex *args, char **argv)
// {
// 	char	*path;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	if (access(argv[3], F_OK) == 0)
// 		args->executable = argv[3];
// 	while (args->path[i] != NULL)
// 	{
// 		command = ft_strjoin("/", args->second_command[0]);
// 		path = ft_strjoin(args->path[i], command);
// 		free(command);
// 		if (access(path, F_OK) == 0)
// 		{
// 			args->executable2 = path;
// 			return ;
// 		}
// 		free(path);
// 		i++;
// 	}
// }

	// print_array(args->path);
	// printf("%s\n",args->executable);
	// printf("%s\n",args->executable2);
	// print_array(args->first_command);
	// print_array(args->second_command);