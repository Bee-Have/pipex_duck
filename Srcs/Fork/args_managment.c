/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:40:09 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/24 17:40:33 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_args(char *cmd)
{
	char	**args;

	if (!cmd)
	{
		error_manager(ERNO_EMPTY_CMD);
		return (NULL);
	}
	args = ft_split(cmd, ' ');
	return (args);
}

int	check_cmd_env(char **cmd, char *env[])
{
	int		i;
	char	*path;
	char	*tmp;
	char	**paths_tab;

	i = 0;
	paths_tab = get_possible_paths(env);
	while (paths_tab[i])
	{
		tmp = ft_strjoin(paths_tab[i], "/");
		path = ft_strjoin(tmp, (*cmd));
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free((*cmd));
			ft_freetab(paths_tab);
			(*cmd) = path;
			return (PATH_OK);
		}
		free(path);
		++i;
	}
	ft_freetab(paths_tab);
	return (error_manager(ERNO_PATH));
}

char	**get_possible_paths(char *env[])
{
	char	*all_paths;
	char	*tmp;
	char	**paths_tab;

	tmp = ft_tabntab(env, "PATH=", 5);
	all_paths = ft_substr(tmp, 4, ft_strlen(tmp) - 5);
	paths_tab = ft_split(all_paths, ':');
	free(tmp);
	free(all_paths);
	return (paths_tab);
}
