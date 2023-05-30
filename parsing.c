/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/30 16:10:35 by dreijans      #+#    #+#                 */
/*   Updated: 2023/05/30 17:26:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	input_parse(char *argv, t_pipex pipex, int fd1, int fd2)
{
	int	i;
	char buffer 

	i = 1;
	pipex.input_file = 
	printf("%s\n", pipex.input_file);
	pipex.output_file = 
	printf("%s\n", pipex.output_file);
	while (argv[i])
	{
		if (i == 1)
			pipex.first_command = &argv[i];
		if (i == 2)
			pipex.second_command = &argv[i];
		i++;
	}
	printf("%s\n", pipex.first_command);
	printf("%s\n", pipex.second_command);
}
