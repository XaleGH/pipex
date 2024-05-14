/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:08:07 by asaux             #+#    #+#             */
/*   Updated: 2024/05/14 13:48:10 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

char	*extract_path(char **env)
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

void	execute(char *av, char **env)
{
	t_path	*path;
	char	*pathfind;
	char	**cmd;

	path = malloc(sizeof(t_path));
	pathfind = get_path(av, env, path);
	cmd = ft_split(av, ' ');
	if (!pathfind)
	{
		free_array(cmd);
		free(path);
		perror("error. path to command not found");
		exit(1);
	}
	if (execve(pathfind, cmd, env) == -1)
	{
		free(pathfind);
		free_array(cmd);
		free(path);
		perror("exec error");
		exit(1);
	}
}
