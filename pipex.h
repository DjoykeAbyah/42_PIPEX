/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipex.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:09 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/08 16:38:18 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "./LIBFT/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

/* check how to find path
commands exist of 2 parts command + flag
*/
typedef struct s_pipex
{
	char	*input_file;
	char	*output_file;
	char	**path;
	char	**first_command;
	char	**second_command;
}							t_pipex;

void	parse_args(char **argv);
void	print_array(char **array);
int		path_acces(char **envp);

#endif
