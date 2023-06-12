/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:09 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/12 14:46:19 by dreijans      ########   odam.nl         */
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

/* check how to find path
commands exist of 2 parts command + flag
*/
typedef struct s_pipex
{
	char	*input_file;
	char	*output_file;
	char	**path;
	char	*executable;
	char	*executable2;
	char	**first_command;
	char	**second_command;
}							t_pipex;

t_pipex		*parse_args(char **argv);
void		print_array(char **array);
void		parse_path(char **envp, t_pipex *args);
void		check_access1(t_pipex *args);
void		check_access2(t_pipex *args);
void		error(char *string, int errno);

#endif
