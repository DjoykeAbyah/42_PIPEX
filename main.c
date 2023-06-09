/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/24 17:03:21 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/09 15:56:04 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*args;
	
	(void) argc;
	args = parse_args(argv);
	parse_path(envp, args);
	check_access(args);
}

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

/* checks if the path acces with access() */
void	check_access(t_pipex *args)
{
	char	*path;
	char	*command;
	char	*flag;
	int		i;
	int		j;

	i = 0;
	while (args->path[i] != NULL)
	{
		j = 0;
		command = ft_strjoin("/", args->first_command[j]);
		j = 1;
		while (args->first_command[j])
		{
			flag = ft_strjoin(" ", args->first_command[j]);
			command = ft_strjoin(command, flag);
			path = ft_strjoin(args->path[i], command);
			if (access(&path[i], X_OK || F_OK) == -1)
				printf("nope\n");
			else
				printf("ye\n");
			j++;
		}
		printf("full path : %s\n", path);
		i++;
	}
}

/* 
int	main(int argc, char **argv, char **envp)
{
	int		fd;
	int		fd2;
	t_pipex	*pipex;

	(void) argc;
	pipex = ft_calloc(sizeof (t_pipex), 1);
	fd = open("file1", O_RDONLY);// open in child want je wilt door met process
	fd2 = open("file2", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(fd, 0);//std output
	dup2(fd2, 1);//swappes output to to stdin //get output in file 2
	execve("/usr/bin/wc", argv, envp);//find the path by myself// use 2 times?
	close (fd);
	close (fd2);
}
*/
