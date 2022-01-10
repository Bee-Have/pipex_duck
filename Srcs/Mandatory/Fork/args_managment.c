/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:40:09 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/10 15:29:07 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_args(char *cmd)
{
	char	*args;

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
	char	**cmd_env;

	i = 0;
	tmp = ft_tabntab(env, "PATH=", 5);
	path = ft_substr(tmp, 4, ft_strlen(tmp) - 5);
	cmd_env = ft_split(path, ':');
	free(tmp);
	while (cmd_env[i])
	{
		free(path);
		tmp = ft_strjoin(cmd_env[i], "/");
		path = ft_strjoin(tmp, (*cmd));
		free(tmp);
		if (access(path, X_OK) == 0)
		{
			free((*cmd));
			ft_freetab(cmd_env);
			(*cmd) = path;
			return (PATH_OK);
		}
		++i;
	}
	free(path);
	ft_freetab(cmd_env);
	error_manager(ERNO_PATH);
	return (PATH_KO);
}
