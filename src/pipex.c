/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:04:02 by asaux             #+#    #+#             */
/*   Updated: 2024/04/11 17:03:30 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char *extract_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH", 4) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char *get_path(char *cmd, char **env, t_path *path)
{
	int	i;

	i = -1;
	path->cmds = ft_split(cmd, ' ');
	path->allpaths = ft_split(extract_path(env), ':');
	while (path->allpaths[++i])
	{
		path->subpath = ft_strjoin(path->allpaths[i], "/");
		path->goodpath = ft_strjoin(path->subpath, path->cmds[0]);
		free(path->subpath);
		if (access(path->goodpath, F_OK | X_OK) == 0)
			{
				free_array(path->allpaths);
				free_array(path->cmds);
				return (path->goodpath);
			}
		free(path->goodpath);
	}
	free_array(path->allpaths);
	free_array(path->cmds);
	return (NULL);
}

void	child_process(char **av, int *fd, char **env)
{
	int file;
	
	file = open(av[1], O_RDONLY, 0777);
	if (file == -1)
	{
		perror("error opening file");
		exit (1);
	}
	dup2(file, STDIN_FILENO);
	close(fd[0]);
	dup2(fd[1], STDOUT_FILENO);
	close(file);
	close(fd[1]);
	execute(av[2], env);
}

void	parent_process(char **av, int *fd, char **env)
{
	int file;

	file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file == -1)
	{
		perror("error opening file");
		exit (1);
	}
	dup2(file, STDOUT_FILENO);
	close(fd[1]);
	dup2(fd[0], STDIN_FILENO);
	close(file);
	close(fd[0]);
	execute(av[3], env);
}

int main(int ac, char **av, char **env)
{
	pid_t	pid;
	int		fd[2];

	if (ac != 5)
	{
		perror("Error. arguments invalid");
		exit(1);
	}
	if (pipe(fd) == -1)
	{
		perror("pipe error");
		exit(1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	if (pid == 0)
		child_process(av, fd, env);
	else
		parent_process(av, fd, env);
	return (0);
}
