/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:10:17 by user42            #+#    #+#             */
/*   Updated: 2021/12/13 17:24:43 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//send : infile/outfile-(int[2]) av env 
//Other function for fork
void	fork_cmds(int files[2], char **cmds, char *env[])
{
	int		i;
	int		cmd_len;
	int		pipefd[2];
	pid_t	*children;

	i = 0;
	//init pid_t
	cmd_len = ft_tablen(cmds);
	children = (pid_t *)malloc(cmd_len * sizeof(pid_t));
	if (!children)
		return (EXIT_FAILURE);
	//pipe
	pipe(pipefd);
	while (i < cmd_len)
	{
		children[i] = fork();
		if (children[i] == 0)
		{
			//dup2 thing
		}
		++i;
	}
}

void	dup2_children(int max, int index, int pipefd[2], int files[2])
{
	int		fd_0;
	int		fd_1;

	if (index == 0)
	{
		fd_0 = files[0];
		fd_1 = pipefd[1];
	}
	else if (index == max)
	{
		fd_0 = pipefd[0];
		fd_1 = files[1];
	}
	else
	{
		fd_0 = pipefd[0];
		fd_1 = pipefd[1];
	}
	dup2(fd_0, 0);
	dup2(fd_1, 1);
	return ;
}
