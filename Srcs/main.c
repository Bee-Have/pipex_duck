/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2021/12/01 15:40:52 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *env[])
{
	int		i;
	char	**cmd_arg;
	int		return_child;
	pid_t	id;

	i = 2;
	printf("ac-[%d]\n", ac);
	while (i < ac)
	{
		id = fork();
		if (id == 0)
		{
			printf("child\n");
			cmd_arg = get_cmd_args(av[i]);
			execve(cmd_arg[0], cmd_arg, env);
			exit(1);
		}
		else
		{
			waitpid(id, &return_child, WUNTRACED);
			printf("parent-[%d][%d]\n", id, return_child);
			++i;
		}
	}
}
