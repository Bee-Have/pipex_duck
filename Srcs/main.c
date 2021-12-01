/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2021/12/01 19:18:33 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *env[])
{
	int		i;
	int		i_id;
	char	**cmd_arg;
	char	*test = NULL;
	// char	test[6];
	int		gnl_ret = 0;
	int		return_child;
	int		pipefd[2];
	pid_t	id[2];

	(void)env;
	i = 2;
	i_id = 0;
	return_child = 0;
	printf("ac-[%d]\n", ac);
	while (i < ac)
	{
		pipe(pipefd);
		id[i_id] = fork();
		if (id[i_id] == 0)
		{
			cmd_arg = get_cmd_args(av[i]);
			printf("cmd-[%s]\n", cmd_arg[0]);
			close(pipefd[0]);
			write(pipefd[1], cmd_arg[0], ft_strlen(cmd_arg[0]));
			// write(pipefd[1], "\n", 1);
			// if (i_id == 0)
			// 	write(pipefd[1], "hello", 6);
			// else if (i_id == 1)
			// 	write(pipefd[1], "world", 6);
			close(pipefd[1]);
			execve(cmd_arg[0], cmd_arg, env);
			exit(1);
		}
		// else
		// {
		// }
		++i;
		++i_id;
	}
	i = 2;
	i_id = 0;
	while (i < ac)
	{
		waitpid(id[i_id], &return_child, WUNTRACED);
		gnl_ret = get_next_line(pipefd[0], &test);
		printf("gnl-[%d]\n", gnl_ret);
		// read(pipefd[0], &test, 5);
		// test[5] = '\0';
		printf("return-[%s]\n", test);
		free(test);
		close(pipefd[1]);
		close(pipefd[0]);
		// ft_bzero(test, 5);
		printf("id-[%d][%d]\n", id[i_id], return_child);
		++i;
		++i_id;
	}
}
