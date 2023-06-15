/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:09 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/15 19:19:58 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./LIBFT/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/errno.h>

# define READ 0
# define WRITE 1

typedef struct s_pipex
{
	char	**argv;
	char	*input_file;
	char	*output_file;
	char	**path;
	char	**first_command;
	char	**second_command;
	int		status;
}							t_pipex;

t_pipex		*parse_args(char **argv);
void		print_array(char **array);
void		parse_path(char **envp, t_pipex *args);
char		*check_access(t_pipex *args, char *base_command);
void		error(char *string, int error);
void		child_1(int *pipe_fd, t_pipex *args, char **envp);
void		child_2(int *pipe_fd, t_pipex *args, char **envp);
void		status_check(int pid2);
void		close_pipes(int *pipe_fd);
void		close_check(int num);
#endif
