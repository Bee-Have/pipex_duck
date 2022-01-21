/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:33:24 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/21 18:47:51 by amarini-         ###   ########.fr       */
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
//here : file[0]=infile | file[1]=outfile | file[2]=stdin
void	dup2_children(int max, int index, int pipefd[2], int files[3])
{
	if (index == 0)
	{
		if (files[0] == NO_INFILE)
			dup2(files[2], 0);
		else
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
		dup2(files[2], 0);
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

