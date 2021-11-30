/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2021/11/30 18:34:20 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	int		return_child;
	pid_t	id;

	(void)av;
	(void)ac;
	id = fork();
	if (id == 0)
	{
		printf("child\n");
		exit(1);
	}
	else
	{
		waitpid(id, &return_child, WUNTRACED);
		printf("parent-[%d][%d]\n", id, return_child);
	}
}
