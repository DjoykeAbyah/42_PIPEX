/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/05/30 18:49:47 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	int		fd;
	int		fd2;
	t_pipex	*pipex;


	(void) argc;
	pipex = ft_calloc(sizeof (t_pipex), 1);
	fd = open("file1", O_RDONLY);
	fd2 = open("file2", O_CREAT);
	dup2(fd, 0);//std output
	dup2(fd2, 1);//swappes output to to stdin //get output in file 2
	execve("/bin/ls", &argv[2], envp);//find the path by myself
	close (fd);
	close (fd2);
}
