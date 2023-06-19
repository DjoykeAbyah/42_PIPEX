/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:17:35 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/19 20:13:48 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* checks exit status, only needs it for the second child because 
everything before the pipe needs no error code everything after needs it
wait is called for child process 1 because i dont need that staus to exit*/
void	status_check(int pid2)
{
	int	status;

	waitpid(pid2, &status, 0);
	wait(NULL);
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
}

void	error(char *string, int error)
{
	perror(string);
	exit(error);
}

void	path_error(int error)
{
	ft_putendl_fd("no such file or directory", 2);
	exit(error);
}

void	close_pipes(int *pipe_fd)
{
	if (pipe_fd)
	{
		if (close(pipe_fd[0]) < 0)
			perror("close pipes");
		if (close(pipe_fd[1]) < 0)
			perror("close pipes");
	}
}

/* check if close failed misschien ook seperate pipe and fd? */
void	close_check(int num)
{
	if (close(num) < 0)
		perror("close");
}

// void	error(char *string, int error)
// {
// 	// write(1, "./pipex: ", 10);
// 	// write(1, string, ft_strlen(string));
// 	// write(1, strerror(errno), ft_strlen(strerror(errno)));
// 	perror(string);
// 	exit(error);
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

	// print_array(args->path);
	// printf("%s\n",args->executable);
	// printf("%s\n",args->executable2);
	// print_array(args->first_command);
	// print_array(args->second_command);