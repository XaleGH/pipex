/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:26:15 by asaux             #+#    #+#             */
/*   Updated: 2024/05/14 13:46:55 by asaux            ###   ########.fr       */
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
