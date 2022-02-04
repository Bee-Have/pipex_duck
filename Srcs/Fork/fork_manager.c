/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:19:52 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/04 18:48:02 by amarini-         ###   ########.fr       */
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
	if (wait_ret == 32512 && files[1] != -1)
		return (127);
	if (wait_ret != 0)
		wait_ret = EXIT_FAILURE;
	return (wait_ret);
}

void	fork_cmds(pid_t *child, int files[2], char **cmds, char *env[])
{
	int		i;
	int		pipefd[2];

	i = 0;
	pipe(pipefd);
	while (i < ft_tablen((const char **)cmds))
	{
		child[i] = fork();
		if (child[i] == 0)
		{
			if (i == ft_tablen((const char **)cmds) - 1 && files[1] == -1)
				exit_child(child, EXIT_FAILURE);
			dup2_child(i, pipefd, files);
			if (check_cmd_env(get_cmd_args(cmds[i]), env) != PATH_OK)
				exit_child(child, 127);
		}
		else if (child[i] != 0 && i == 0)
			close(files[0]);
		++i;
	}
	close(pipefd[0]);
	close(pipefd[1]);
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
	if (wait_ret == 32512 && files[1] != -1)
		return (127);
	if (wait_ret != 0)
		wait_ret = EXIT_FAILURE;
	return (wait_ret);
}

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
//here : pipes[0][2] -> pipes fork | pipes[1][2] -> pipes here_doc
void	fork_cmds(pid_t *child, int files[3], char ***cmds, char *env[])
{
	int		i;
	int		pipes[2][2];

	i = 0;
	while (i < ft_tablen((const char **)*cmds))
	{
		pipe(pipes[0]);
		if (i == 0 && files[0] == NO_INFILE)
			here_doc_manager(cmds, &(pipes[1]));
		child[i] = fork();
		if (child[i] == 0)
		{
			if (i == ft_tablen((const char **)*cmds) - 1 && files[1] == -1)
				exit_child(child, EXIT_FAILURE);
			if (files[0] == NO_INFILE)
				dup_close_fd(pipes[1][0], 0);
			dup2_child(ft_tablen((const char **)*cmds) - 1, i, pipes[0], files);
			if (check_cmd_env(get_cmd_args((*cmds)[i]), env) != PATH_OK)
				exit_child(child, 127);
		}
		else
			transit_pipe(i, pipes[0], pipes[1], files);
		++i;
	}
}

#endif
