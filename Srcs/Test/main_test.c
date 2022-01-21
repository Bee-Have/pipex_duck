/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2022/01/21 17:18:47 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "pipex.h"
// #include "../Libs/libft_duck/Includes/libft.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);

char	**get_cmd_args(char *cmd)
{
	char	*path;
	char	**args;

	if (!cmd)
		return (NULL);
	args = ft_split(cmd, ' ');
	path = ft_strjoin("/bin/", args[0]);
	free(args[0]);
	args[0] = path;
	return (args);
}

int	main(int ac, char **av, char *env[])
{
	int		i;
	int		i_id;
	int		infile;
	int		outfile;
	int		id_len;
	char	**cmd_arg;
	int		return_child;
	int		pipefd[2];
	int		fd_cpy;
	pid_t	*id;

	fd_cpy = dup(STDIN_FILENO);
	printf("ac-[%d]\n", ac);
	i = 2;
	infile = open(av[1], O_RDONLY);
	outfile = open(av[ac - 1], O_RDWR);
	i_id = 0;
	id_len = ac - 3;
	id = (pid_t *)malloc(id_len * sizeof(pid_t));
	if (!id)
		return(EXIT_FAILURE);
	while (i_id < id_len)
	{
		id[i_id] = -1;
		++i_id;
	}
	i_id = 0;
	return_child = 0;
	while (i < (ac - 1))
	{
		pipe(pipefd);
		id[i_id] = fork();
		if (id[i_id] == 0)
		{
			printf("n.%d\n", i_id);
			if (i_id == 0)
			{
				printf("first child\n");
				dup2(infile, 0);
				dup2(pipefd[1], 1);
			}
			else if (i_id == (id_len - 1))
			{
				printf("last child\n");
				dup2(fd_cpy, 0);
				dup2(outfile, 1);
			}
			else
			{
				printf("middle child\n");
				dup2(fd_cpy, 0);
				dup2(pipefd[1], 1);
			}
			cmd_arg = get_cmd_args(av[i]);
			close(pipefd[0]);
			close(pipefd[1]);
			execve(cmd_arg[0], cmd_arg, env);
			exit(1);
		}
		else
		{
			dup2(fd_cpy, pipefd[0]);
			close(pipefd[0]);
			close(pipefd[1]);
		}
		++i;
		++i_id;
	}
	i_id = 0;
	while (i_id < id_len)
	{
		waitpid(id[i_id], &return_child, WUNTRACED);
		++i_id;
	}
	close(infile);
	close(outfile);
	free(id);
}
