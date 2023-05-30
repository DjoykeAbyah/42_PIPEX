/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/05/30 17:55:11 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// int	main(int argc, char **argv, char **envp)

int	main(int argc, char **argv)
{
	int		fd;
	int		fd2;
	t_pipex	*pipex;

	(void) argc;
	pipex = ft_calloc(sizeof (t_pipex), 1);
	fd = open("file1", O_RDONLY);
	fd2 = open("file2", O_CREAT);
	// while (1)
	// {
	// 	printf("done");
	// 	return (EXIT_SUCCESS);
	// }
	// if (argc <= 1)
	// 	return (EXIT_FAILURE);
	input_parse(*argv, *pipex, fd, fd2);
	close (fd);
	close (fd2);
}
