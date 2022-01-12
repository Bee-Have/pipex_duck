/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:19:52 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/12 16:48:14 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
int	fork_manager(int files[2], char **cmds, char *env[])
{
	int		len_cmds;
	int		ret_fork;
	int		pipefd[2];
	pid_t	*child;

	len_cmds = ft_tablen((const char **)cmds);
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	//pipe
	pipe(pipefd);
	//function to fork
	ret_fork = fork_cmds(child, files, pipefd, cmds, env);
	if (ret_fork == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//function to waitpid
	wait_for_children(child, len_cmds);
	return (EXIT_SUCCESS);
}

int	fork_cmds(pid_t *child, int files[2], int pipefd[2], char **cmds, char *env[])
{
	int		i;
	int		len;
	char	**cmd_args;

	i = 0;
	len = ft_tablen((const char **)cmds);
	cmd_args = NULL;
	while (i < len)
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			dup2_children(i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			close(pipefd[0]);
			if (check_cmd_env(&cmd_args[0], env) == PATH_OK)
				execve(cmd_args[0], cmd_args, env);
			else
				return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

#else
int	fork_manager(int pipefd[2], int files[2], char **cmds, char *env[])
{
	int		len_cmds;
	int		ret_fork;
	pid_t	*child;

	len_cmds = ft_tablen((const char **)cmds);
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	ret_fork = fork_cmds(child, files, pipefd, cmds, env);
	if (ret_fork == EXIT_FAILURE)
		return (EXIT_FAILURE);
	wait_for_children(child, len_cmds);
	return (EXIT_SUCCESS);
}

int	fork_cmds(pid_t *child, int files[2], int pipefd[2], char **cmds, char *env[])
{
	int		i;
	int		len;
	char	**cmd_args;

	i = 0;
	len = ft_tablen((const char **)cmds);
	cmd_args = NULL;
	while (i < len)
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			dup2_children(len - 1, i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			close(pipefd[0]);
			if (check_cmd_env(&cmd_args[0], env) == PATH_OK)
				execve(cmd_args[0], cmd_args, env);
			else
				return (EXIT_FAILURE);
		}
		++i;
	}
	return (EXIT_SUCCESS);
}

#endif

