/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaux <asaux@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 03:01:41 by asaux             #+#    #+#             */
/*   Updated: 2024/05/14 13:44:03 by asaux            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include "../libft/libft.h"
# include <fcntl.h>

typedef struct s_path
{
	char	**cmds;
	char	**allpaths;
	char	*goodpath;
	char	*subpath;
}	t_path;

//pipex.c

char	*extract_path(char **env);
char	*get_path(char *cmd, char **env, t_path *path);
int		main(int ac, char **av, char **env);
void	child_process(char **av, int *fd, char **env);
void	parent_process(char **av, int *fd, char **env);

//pipex_utils.c

void	free_array(char **array);
void	execute(char *av, char **env);

//pipex_bonus.c

char	*get_path(char *cmd, char **env, t_path *path);
int		main(int ac, char **av, char **env);
void	here_doc(int ac, char **av, char **env);
int		here_doc_init(char **av);
void	init_pipe(char *av, char **env);

//pipex_utils_bonus.c

void	free_array(char **array);
void	execute(char *av, char **env);
char	*extract_path(char **env);

//Get_Next_Line

char	*get_next_line(int fd);

#endif