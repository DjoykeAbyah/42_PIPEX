/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/09 16:53:51 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;

	(void) argc;
	args = parse_args(argv);
	parse_path(envp, args);
	check_access(args);
}

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
