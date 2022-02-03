/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:40:09 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/03 14:22:54 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_args(char *cmd)
{
	char	**args;

	if (!cmd)
	{
		error_manager(ERNO_EMPTY_CMD, NULL);
		return (NULL);
	}
	args = ft_split(cmd, ' ');
	return (args);
}

int	check_cmd_env(char **cmd, char *env[])
{
	int		i;
	char	*path;
	char	**paths_tab;

	i = 0;
	if (access(cmd[0], X_OK) == 0)
		execve(cmd[0], cmd, env);
	paths_tab = get_possible_paths(env);
	while (paths_tab[i])
	{
		path = ft_strjoin(paths_tab[i], cmd[0]);
		if (access(path, X_OK) == 0)
		{
			free(cmd[0]);
			ft_freetab(paths_tab);
			cmd[0] = path;
			execve(cmd[0], cmd, env);
		}
		free(path);
		++i;
	}
	ft_freetab(paths_tab);
	
	return (error_manager(ERNO_PATH, cmd[0]));
}

char	**get_possible_paths(char *env[])
{
	char	*all_paths;
	char	*tmp;
	char	**paths_tab;
	int		i;

	i = 0;
	tmp = ft_tabntab(env, "PATH=", 5);
	all_paths = ft_substr(tmp, 4, ft_strlen(tmp) - 5);
	paths_tab = ft_split(all_paths, ':');
	while (paths_tab[i])
	{
		free(tmp);
		tmp = ft_strjoin(paths_tab[i], "/");
		free(paths_tab[i]);
		paths_tab[i] = ft_strdup(tmp);
		++i;
	}
	free(tmp);
	free(all_paths);
	return (paths_tab);
}
