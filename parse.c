/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:53:00 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/15 21:09:14 by dreijans      ########   odam.nl         */
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
	args->path = NULL;
	args->status = 0;
	args->argv = argv;
	return (args);
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
			free (path);
			if (args->path == NULL)
				error ("path", errno);
		}
		i++;
	}
}

/* checks if the path acces with access() for the first command */
char	*check_access(t_pipex *args, char *base_command)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	if (ft_strchr(base_command, '/'))
		return (base_command);
	while (args->path && args->path[i] != NULL)
	{
		command = ft_strjoin("/", base_command);
		path = ft_strjoin(args->path[i], command);
		free(command);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (base_command);
}

char	*check_executable(t_pipex *args)///can we fix it? yes we can!
{
	int		i;
	char	*executable;

	i = 0;
	while (args != NULL)
	{
		if (!args)
			error(args->flexible_command, yes?, errno);
		if (args == " ")
			error(args->flexible_command, yes?, errno);
		i++;
	}
	executable = check_access(args, args->first_command[0]);
	if (access(executable, X_OK) == -1)
		error(executable, errno);
	return (executable);
}
