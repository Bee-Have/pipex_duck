/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_managment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 14:56:34 by user42            #+#    #+#             */
/*   Updated: 2021/12/28 14:54:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_cmd_args(char *cmd)
{
	char	**args;

	// printf("getting args for cmd");
	if (!cmd)
		return (NULL);
	args = ft_split(cmd, ' ');
	// args[0] = NULL;
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
	free(path);
	free(tmp);
	while (cmd_env[i] != NULL)
	{
		tmp = ft_strjoin(cmd_env[i], "/");
		path = ft_strjoin(tmp, (*cmd));
		if (access(path, X_OK) == 0)
		{
			// printf("SUCESS in accessing path\n");
			free((*cmd));
			(*cmd) = path;
			return (PATH_OK);
		}
		free(path);
		free(tmp);
		++i;
	}
	print_error(ERNO_PATH);
	return (PATH_KO);
}
