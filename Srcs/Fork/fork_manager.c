/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:19:52 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/24 15:25:45 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	fork_manager(int files[2], char **cmds, char *env[])
{
	int		len_cmds;
	int		ret_fork;
	pid_t	*child;

	len_cmds = ft_tablen((const char **)cmds);
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	ret_fork = fork_cmds(child, files, cmds, env);
	if (ret_fork == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_for_children(child, len_cmds);
	free(child);
	return (EXIT_SUCCESS);
}

int	fork_cmds(pid_t *child, int files[2], char **cmds, char *env[])
{
	int		i;
	int		pipefd[2];
	char	**cmd_args;

	i = 0;
	pipe(pipefd);
	while (i < ft_tablen((const char **)cmds))
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			dup2_children(i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			if (check_cmd_env(&cmd_args[0], env) == PATH_OK)
				execve(cmd_args[0], cmd_args, env);
			else
				return (EXIT_FAILURE);
		}
		else if (child[i] != 0 && i == 0)
			close(files[0]);
		++i;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (EXIT_SUCCESS);
}

#else

int	fork_manager(int files[3], char **cmds, char *env[])
{
	int		len_cmds;
	int		ret_fork;
	pid_t	*child;

	len_cmds = ft_tablen((const char **)cmds);
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	ret_fork = fork_cmds(child, files, cmds, env);
	if (ret_fork == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_for_children(child, len_cmds);
	free(child);
	return (EXIT_SUCCESS);
}

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
int	fork_cmds(pid_t *child, int files[3], char **cmds, char *env[])
{
	int		i;
	int		len;
	int		pipefd[2];
	char	**cmd_args;

	i = 0;
	len = ft_tablen((const char **)cmds);
	while (i < len)
	{
		pipe(pipefd);
		child[i] = fork();
		if (child[i] == 0)
		{
			dup2_children(len - 1, i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			if (check_cmd_env(&cmd_args[0], env) == PATH_OK)
				execve(cmd_args[0], cmd_args, env);
			else
				return (EXIT_FAILURE);
		}
		else
			transit_pipe(pipefd, files);
		++i;
	}
	return (EXIT_SUCCESS);
}

#endif
