/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:53:00 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/09 16:53:40 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* intitializing my struct */
t_pipex	*parse_args(char **argv)
{
	t_pipex	*args;

	args = ft_calloc(sizeof (t_pipex), 1);
	args->input_file = argv[1];
	args->output_file = argv[4];
	args->first_command = ft_split(argv[2], ' ');
	args->second_command = ft_split(argv[3], ' ');
	return (args);
}

/* prints arrays, for testing */
void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_printf("%s\n", array[i]);
		i++;
	}	
}

/* finds the PATH and stores it in a struct as a 2D array*/
void	parse_path(char **envp, t_pipex *args)
{
	int		i;
	char	*path;	

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			args->path = ft_split(path, ':');
		}
		i++;
	}
}

/* checks if the path acces with access()
zorg strjoin's freed  //&path[i] checks the character dumb dumb */
void	check_access(t_pipex *args)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	while (args->path[i] != NULL)
	{
		command = ft_strjoin("/", args->first_command[0]);
		path = ft_strjoin(args->path[i], command);
		free(command);
		if (access(path, F_OK) == 0)
		{
			args->executable = path;
			return ;
		}
		free(path);
		i++;
	}
	//zorg dat er iets gebeurd als de executable er niet is check bash error 
	//No such file or directory// bash: /usr/bin/me: No such file or directory
}