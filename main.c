/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/05/30 12:53:59 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "pipex.h"

// int	main(int argc, char **argv, char **envp)

int	main(void)
{
	int	fd;
	int fd2;

	fd = open("file1", O_RDONLY);
	fd2 = open("file2", O_CREAT);
	while (1)
	{
		printf("done");
		return (EXIT_SUCCESS);
	}
}
