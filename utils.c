/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/14 14:17:35 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/17 17:14:56 by dreijans      ########   odam.nl         */
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

/* error message with perror */
void	ft_error(char *string, int error)
{
	perror(string);
	exit(error);
}

/* error when space or empty string is found */
void	null_space_error(char *string, int error)
{
	ft_putstr_fd(string, 2);
	exit(error);
}

/* closes pipes and checks if it succeeded */
void	close_pipes(int *pipe_fd)
{
	if (pipe_fd)
	{
		if (close(pipe_fd[0]) < 0)
			perror("close");
		if (close(pipe_fd[1]) < 0)
			perror("close");
	}
}

/* gives custom error when command is not found */
void	command_error(char *string, int error)
{
	ft_putstr_fd(string, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd("Command not found", 2);
	exit(error);
}
