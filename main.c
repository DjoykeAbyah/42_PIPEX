/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/17 18:12:30 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	int		pid[2];
	int		pipe_fd[2];

	if (argc != 5)
		ft_error("./pipex: incorrect arguments", errno);
	args = parse_args(argv);
	if (pipe(pipe_fd) == -1)
		ft_error("pipe", errno);
	pid[0] = fork();
	if (pid[0] < 0)
		ft_error("fork", errno);
	if (pid[0] == 0)
		child_1(pipe_fd, args, envp, argv);
	pid[1] = fork();
	if (pid[1] < 0)
		ft_error("fork", errno);
	if (pid[1] == 0)
		child_2(pipe_fd, args, envp, argv);
	close_pipes(pipe_fd);
	status_check(pid[1]);
}
