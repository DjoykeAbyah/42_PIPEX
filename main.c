/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 00:19:54 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	int		pid;
	int		pipe_fd[2];
	int		fd;

	if (argc != 5)
		ft_printf("too few arguments");
	args = parse_args(argc, argv);
	parse_path(envp, args);
	check_access(args);
	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid < 0)
		return (2);
	if (pid == 0)//child process 
	{
		close(pipe_fd[READ]);
		fd = open("file1", O_RDONLY);
		if (fd == -1)
			return (3);//exit?
		dup2(fd, STDIN_FILENO);
		close(fd); //pas als ik hem gebruikt heb????
		//write outcome exeve fd to pipe_fd[WRITE]???
		execve(const char *pathname, char *const argv[], char *const envp[])
	}
	//main process
	//close(fd[WRITE])
	//redirect STD_OUT to file2!
}

//improve error handling
//create process!

/* 
int	main(int argc, char **argv, char **envp)
{
	int		fd;
	int		fd2;
	t_pipex	*pipex;

	(void) argc;
	pipex = ft_calloc(sizeof (t_pipex), 1);
	fd = open("file1", O_RDONLY);// open in child want je wilt door met process
	fd2 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 0);//std output
	dup2(fd2, 1);//swappes output to to stdin //get output in file 2
	execve("/usr/bin/wc", argv, envp);//find the path by myself// use 2 times?
	close (fd);
	close (fd2);
}
*/
