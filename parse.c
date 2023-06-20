/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:53:00 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/20 11:18:08 by dreijans      ########   odam.nl         */
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
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			args->path = ft_split(path, ':');
			free (path);
			if (args->path == NULL)
				error ("malloc", errno);
			return ;
		}
		i++;
	}
	// want to put this error somewhere else not needed here?????????
	// path_error(*args->first_command, *args->second_command, errno);
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
	if (base_command[0] == '/' || ft_strncmp(base_command, "./", 2) == 0)
		return (base_command);
	if (access(base_command, X_OK) == 0)
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

/* checks if string is empty or has space at index 0 */
void	check_space_and_null(char *string)
{
	if (string[0] == '\0')
		null_space_error("pipex: command not found\n", errno);
	else if (string[0] == ' ')
		null_space_error("pipex: command not found\n", errno);
}

/* check if close failed misschien ook seperate pipe and fd? */
void	close_check(int num)
{
	if (close(num) < 0)
		perror("close");
}
