/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:09 by dreijans      #+#    #+#                 */
/*   Updated: 2023/05/30 17:37:21 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./LIBFT/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_pipex
{
	char	*input_file;
	char	*output_file;
	char	*first_command;
	char	*second_command;
}							t_pipex;

void	input_parse(char *argv, t_pipex pipex, int fd1, int fd2);

#endif
