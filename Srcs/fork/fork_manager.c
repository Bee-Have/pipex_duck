/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 17:10:17 by user42            #+#    #+#             */
/*   Updated: 2022/01/05 15:35:52 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//send : infile/outfile-(int[2]) av env 
//Other function for fork
int	fork_cmds(int pipefd[2], int files[2], char **cmds, char *env[])
{
	int		i;
	// int		pipefd[2];
	pid_t	*children;
	char	**cmd_args;

	i = 0;
	children = (pid_t *)malloc(ft_tablen((const char **)cmds) * sizeof(pid_t));
	if (!children)
		return (EXIT_FAILURE);
	// pipe(pipefd);
	// printf("cmds nbr [%d]\n", ft_tablen((const char **)cmds));
	while (i < ft_tablen((const char **)cmds))
	{
		children[i] = fork();
		if (children[i] == 0)
		{
			dup2_children(ft_tablen((const char **)cmds) - 1, i, pipefd, files);
			cmd_args = get_cmd_args(cmds[i]);
			close(pipefd[0]);
			if (check_cmd_env(&cmd_args[0], env) == PATH_OK)
				execve(cmd_args[0], cmd_args, env);
			else
				return (EXIT_FAILURE);
		}
		++i;
	}
	wait_for_children(/*children, */ft_tablen((const char **)cmds));
	return (EXIT_SUCCESS);
}

void	wait_for_children(/*pid_t *children,*/ int size)
{
	int		i;
	int		ret_child;

	i = 0;
	ret_child = 0;
	while (i < size)
	{
		waitpid(-1, &ret_child, WUNTRACED);
		++i;
	}
	return ;
}

void	dup2_children(int max, int index, int pipefd[2], int files[2])
{
	if (index == 0)
	{
		dup2(files[0], 0);
		dup2(pipefd[1], 1);
	}
	else if (index == max)
	{
		dup2(pipefd[0], 0);
		dup2(files[1], 1);
	}
	else
	{
		dup2(pipefd[0], 0);
		dup2(pipefd[1], 1);
	}
}
