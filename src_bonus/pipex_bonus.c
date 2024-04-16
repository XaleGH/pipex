/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 00:07:24 by asaux             #+#    #+#             */
/*   Updated: 2024/04/11 17:08:07 by asaux            ###   ########.fr       */
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

}

void	here_doc(int ac, char **av, char **env)
{
	
}

int	here_doc_init(char **av)
{

}

int	main(int ac, char **av, char **env)
{

}
