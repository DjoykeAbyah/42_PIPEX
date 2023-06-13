/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/09 16:53:00 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/13 15:49:52 by dreijans      ########   odam.nl         */
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
	return (args);
}

/* finds the PATH and stores it in a struct as a 2D array*/
void	parse_path(char **envp, t_pipex *args)
{
	int		i;
	char	*path;	

	i = 0;
	while (envp && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			args->path = ft_split(path, ':');
			if (args->path == NULL)
				error ("path", errno);
		}
		i++;
	}
}

/* checks if the path acces with access() for the first command */
void	check_access1(t_pipex *args, char **argv)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	if (access(argv[2], F_OK) == 0)
	{
		args->executable = argv[2];
		return ;
	}
	if (!args->path)
		args->path = ft_split(argv[2], ':');
	if (!args->path)
		error("path", errno);
	while (args->path[i] != NULL)
	{
		if (args->first_command[0][0] != '/')// can this be a different function?
			command = ft_strjoin("/", args->first_command[0]);//
		else//
			command = ft_strjoin("", args->first_command[0]);//
		path = ft_strjoin(args->path[i], command);//
		free(command);//
		if (access(path, F_OK) == 0)
		{
			args->executable = path;
			return ;
		}
		free(path);
		i++;
	}
}

/* checks if the path acces with access() for the second command */
void	check_access2(t_pipex *args, char **argv)
{
	char	*path;
	char	*command;
	int		i;

	i = 0;
	if (access(argv[3], F_OK) == 0)
	{
		args->executable2 = argv[3];
		return ;
	}
	if (!args->path)
		args->path = ft_split(argv[3], ':');
	if (!args->path)
		error("path", errno);
	while (args->path[i] != NULL)
	{
		path = command_check(args->second_command);
		// if (args->second_command[0][0] != '/') // can this be a different function?
		// 	command = ft_strjoin("/", args->second_command[0]);//
		// else//
		// 	command = ft_strjoin("", args->second_command[0]);//
		// path = ft_strjoin(args->path[i], command);//
		// free(command);//
		if (access(path, F_OK) == 0)
		{
			args->executable2 = path;
			return ;
		}
		free(path);
		i++;
	}
}

void	error(char *string, int error)
{
	// write(1, "./pipex: ", 10);
	// write(1, string, ft_strlen(string));
	// write(1, strerror(errno), ft_strlen(strerror(errno)));
	perror(string);
	exit(error);
}

/*function to reduce line count of access check but is not working properly*/
// char	*command_check(t_pipex *args)
// {
// 	char	*command;
// 	int		i;

// 	i = 0
// 	if (args->second_command[0][0] != '/')
// 		command = ft_strjoin("/", args->second_command[0]);
// 	else
// 		command = ft_strjoin("", args->second_command[0]);
// 	path = ft_strjoin(args->path[i], command);
// 	free(command);
// 	return (path);
// }

// void	fd_check(int fd1, int fd2)
// {
// }

/* prints arrays, for testing */
// void	print_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i] != NULL)
// 	{
// 		ft_printf("%s\n", array[i]);
// 		i++;
// 	}	
// }

// /* checks if the path acces with access() for the first command.
// zorg strjoin's freed  //&path[i] checks the character dumb dumb
// //need to make it for the seconds command? */
// void	check_access1(t_pipex *args, char **argv)
// {
// 	char	*path;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	if (access(argv[2], F_OK) == 0)
// 		args->executable = argv[2];
// 	while (args->path[i] != NULL)
// 	{
// 		command = ft_strjoin("/", args->first_command[0]);
// 		path = ft_strjoin(args->path[i], command);
// 		free(command);
// 		if (access(path, F_OK) == 0)
// 		{
// 			args->executable = path;
// 			return ;
// 		}
// 		free(path);
// 		i++;
// 	}
// }

// /* checks if the path acces with access() for the first command.
// zorg strjoin's freed  //&path[i] checks the character dumb dumb
// //need to make it for the seconds command? */
// void	check_access2(t_pipex *args, char **argv)
// {
// 	char	*path;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	if (access(argv[3], F_OK) == 0)
// 		args->executable = argv[3];
// 	while (args->path[i] != NULL)
// 	{
// 		command = ft_strjoin("/", args->second_command[0]);
// 		path = ft_strjoin(args->path[i], command);
// 		free(command);
// 		if (access(path, F_OK) == 0)
// 		{
// 			args->executable2 = path;
// 			return ;
// 		}
// 		free(path);
// 		i++;
// 	}
// }

	// print_array(args->path);
	// printf("%s\n",args->executable);
	// printf("%s\n",args->executable2);
	// print_array(args->first_command);
	// print_array(args->second_command);