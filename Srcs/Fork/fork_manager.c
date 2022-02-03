/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:19:52 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/03 17:11:16 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	fork_manager(int files[2], char **cmds, char *env[])
{
	int		len_cmds;
	int		wait_ret;
	pid_t	*child;

	len_cmds = ft_tablen((const char **)cmds);
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	fork_cmds(child, files, cmds, env);
	wait_ret = wait_for_children(child, len_cmds);
	if (wait_ret == 32512)
		return (127);
	return (wait_ret);
}

int	fork_cmds(pid_t *child, int files[2], char **cmds, char *env[])
{
	int		i;
	int		pipefd[2];
	int		ret;
	char	**cmd_args;

	i = 0;
	pipe(pipefd);
	ret = EXIT_SUCCESS;
	while (i < ft_tablen((const char **)cmds))
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			dup2_children(i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			ret = check_cmd_env(cmd_args, env);
			if (ret != PATH_OK)
			{
				ft_freetab(cmd_args);
				free(child);
				ret = 127;
				exit(127);
			}
		}
		else if (child[i] != 0 && i == 0)
			close(files[0]);
		++i;
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return (ret);
}

#else

int	fork_manager(int files[3], char ***cmds, char *env[])
{
	int		len_cmds;
	int		wait_ret;
	pid_t	*child;

	len_cmds = ft_tablen((const char **)*cmds);
	if (files[0] == NO_INFILE)
		--len_cmds;
	child = (pid_t *)malloc(len_cmds * sizeof(pid_t));
	if (!child)
		return (EXIT_FAILURE);
	fork_cmds(child, files, cmds, env);
	wait_ret = wait_for_children(child, len_cmds);
	if (wait_ret == 32512)
		return (127);
	return (wait_ret);
}

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
int	fork_cmds(pid_t *child, int files[3], char ***cmds, char *env[])
{
	int		i;
	int		ret;
	int		pipefd[2];
	int		pipehd[2];
	char	**cmd_args;

	i = 0;
	ret = EXIT_SUCCESS;
	while (i < ft_tablen((const char **)*cmds))
	{
		pipe(pipefd);
		if (i == 0 && files[0] == NO_INFILE)
			here_doc_manager(cmds, &pipehd);
		child[i] = fork();
		if (child[i] == 0)
		{
			if (files[0] == NO_INFILE)
				dup_close_fd(pipehd[0], 0);
			dup2_children(ft_tablen((const char **)*cmds), i, pipefd, files);
			cmd_args = get_cmd_args((*cmds)[i]);
			ret = check_cmd_env(cmd_args, env);
			if (ret != PATH_OK)
			{
				ft_freetab(cmd_args);
				free(child);
				ret = 127;
				exit(127);
			}
		}
		else
			transit_pipe(i, pipefd, pipehd, files);
		++i;
	}
	return (ret);
}

#endif
