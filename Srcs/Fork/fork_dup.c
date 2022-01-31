/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_dup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:33:24 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/31 12:42:13 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

void	dup2_children(int index, int pipefd[2], int files[2])
{
	if (index == 0)
	{
		dup_close_fd(files[0], 0);
		dup_close_fd(pipefd[1], 1);
	}
	else
	{
		dup_close_fd(pipefd[0], 0);
		dup_close_fd(files[1], 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(files[1]);
}

#else

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
void	dup2_children(int max, int index, int pipefd[2], int files[3])
{
	--max;
	if (index == 0)
	{
		if (files[0] != NO_INFILE)
			dup_close_fd(files[0], 0);
		dup_close_fd(pipefd[1], 1);
	}
	else if (index == max)
	{
		dup_close_fd(files[2], 0);
		dup_close_fd(files[1], 1);
	}
	else
	{
		dup_close_fd(files[2], 0);
		dup_close_fd(pipefd[1], 1);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	if (files[0] != NO_INFILE)
		close(files[0]);
	close(files[1]);
	close(files[2]);
}

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
void	transit_pipe(int i, int pipefd[2], int pipehd[2], int files[3])
{
	if (i == 0 && files[0] != NO_INFILE)
		close(files[0]);
	else if (i == 0 && files[0] == NO_INFILE)
		close(pipehd[0]);
	dup_close_fd(pipefd[0], files[2]);
	close(pipefd[1]);
	return ;
}

#endif

void	dup_close_fd(int fd, int std)
{
	dup2(fd, std);
	close(fd);
}
