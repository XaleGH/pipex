/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:24 by asaux             #+#    #+#             */
/*   Updated: 2024/05/03 16:12:07 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

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

void	init_pipe(char *av, char **env)
{
	int	fd[2];
	int	pid;

	if (pipe(fd) == -1)
	{
		perror("pipe init error");
		exit (1);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork error");
		exit(1);
	}
	else if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		execute(av, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
	}
}

void	here_doc(int ac, char **av, char **env)
{
	int	file1;
	int	file2;
	int	i;

	i = 3;
	if (ac < 6)
	{
		exit(1);
		perror("error running program");
	}
	here_doc_init(av);
	file1 = open("here_doc", O_RDONLY, 0777);
	file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (file1 == -1 || file2 == -1)
	{
		perror("error opening file");
		exit(1);
	}
	dup2(file1, 0);
	while (i < ac - 2)
		init_pipe(av[i++], env);
	dup2(file2, 1);
	execute(av[ac - 2], env);
}

int	here_doc_init(char **av)
{
	char	*line;
	int		file1;

	line = NULL;
	file1 = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (file1 == -1)
	{
		perror("error opening file");
		exit(1);
	}
	while (1)
	{
		write(1, "pipe here_doc>", 14);
		line = get_next_line(0);
		if (!line)
			return (1);
		if (ft_strlen(av[2]) + 1 == ft_strlen(line)
			&& ft_strncmp(line, av[2], ft_strlen(av[2])) == 0)
			return (free(line), 0);
		ft_putstr_fd(line, file1);
		free(line);
	}
	close(file1);
	return (1);
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	file1;
	int	file2;
	
	if (ac < 5)
	{
		perror("Error running program");
		exit (1);
	}
	if (ft_strncmp(av[1], "here_doc", 7) == 0)
	{
		i = 3;
		here_doc(ac, av, env);
	}
	i = 2;
	file1 = open(av[1], O_RDONLY, 0777);
	file2 = open(av[ac - 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	dup2(file1, 0);
	while (i < ac - 2)
		init_pipe(av[i++], env);
	dup2(file2, 1);
	execute(av[ac - 2], env);
	return (0);
}
