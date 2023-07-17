/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:09 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/17 18:13:41 by dreijans      ########   odam.nl         */
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
# include <stdbool.h>

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
bool		parse_path(char **envp, t_pipex *args);
char		*check_access(char **envp, t_pipex *args, char *base_command);
void		ft_error(char *string, int error);
void		child_1(int *pipe_fd, t_pipex *args, char **envp, char **argv);
void		child_2(int *pipe_fd, t_pipex *args, char **envp, char **argv);
void		status_check(int pid2);
void		close_pipes(int *pipe_fd);
void		close_check(int num);
void		check_space_and_null(char *string);
void		null_space_error(char *string, int error);
void		command_error(char *string, int error);
bool		absolute_check(char *base_command);

#endif
