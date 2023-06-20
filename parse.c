/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:53:00 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/20 19:38:38 by dreijans      ########   odam.nl         */
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
bool	parse_path(char **envp, t_pipex *args)
{
	int		i;
	char	*temp_path;	

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			temp_path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (temp_path == NULL)
				error ("malloc", errno);
			args->path = ft_split(temp_path, ':');
			if (args->path == NULL)
				error ("malloc", errno);
			free (temp_path);
			if (args->path == NULL)
				error ("malloc", errno);
			return (true);
		}
		i++;
	}
	return (false);
}

void	path_check(char *base_command)
{
	if (!ft_strncmp(base_command, "/", 1) && access(base_command, F_OK) == 0)
		return (base_command);
	if (!ft_strncmp(base_command, "./", 2) && access(base_command, F_OK) == 0)
		return (base_command);
	if (!ft_strncmp(base_command, "../", 3) && access(base_command, F_OK) == 0)
		return (base_command);
}

/* checks if the path acces with access() for the first command */
char	*check_access(char **envp, t_pipex *args, char *base_command)
{
	char	*ok_path;
	char	*command;
	int		i;

	i = 0;
	path_check(base_command);
	if (parse_path(envp, args))
	{	
		while (args->path && args->path[i] != NULL)
		{
			command = ft_strjoin("/", base_command);
			if (command == NULL)
				error("malloc", errno);
			ok_path = ft_strjoin(args->path[i], command);
			if (command == NULL)
				error("malloc", errno);
			free(command);
			if (access(ok_path, F_OK) == 0)
				return (ok_path);
			free(ok_path);
			i++;
		}
		command_error(base_command, errno);
	}
	return (base_command);
}

/* checks if string is empty or has space at index 0 */
void	check_space_and_null(char *string)
{
	if (string[0] == '\0')
		null_space_error("pipex: command not found\n", errno);
	else if (string[0] == ' ')
		null_space_error("pipex: command not found\n", errno);
}
