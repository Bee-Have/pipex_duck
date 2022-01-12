/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:33:24 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/12 16:43:00 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
void	dup2_children(int index, int pipefd[2], int files[2])
{
	if (index == 0)
	{
		dup2(files[0], 0);
		dup2(pipefd[1], 1);
	}
	else
	{
		dup2(pipefd[0], 0);
		dup2(files[1], 1);
	}
}
#else
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

#endif

void	wait_for_children(pid_t *children, int size)
{
	int	i;
	int	ret_child;

	i = 0;
	ret_child = 0;
	while (i < size)
	{
		waitpid(children[i], &ret_child, WUNTRACED);
		++i;
	}
}
