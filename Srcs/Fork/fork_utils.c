/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:51:39 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/04 18:45:59 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exit_child(pid_t *children, int ret)
{
	free(children);
	exit(ret);
}

int	wait_for_children(pid_t *children, int size)
{
	int	ret_child;
	int	i;

	i = 0;
	while (i < size)
	{
		ret_child = 0;
		waitpid(children[i], &ret_child, WUNTRACED);
		++i;
	}
	free(children);
	return (ret_child);
}
