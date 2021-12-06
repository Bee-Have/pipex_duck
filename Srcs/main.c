/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:14:53 by user42            #+#    #+#             */
/*   Updated: 2021/12/06 18:15:19 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char *env[])
{
	int		i;
	int		i_id;
	int		id_len;
	char	**cmd_arg;
	char	*test = NULL;
	char	*cmd;
	int		return_child;
	int		pipefd[2];
	pid_t	*id;

	i = 2;
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
	pipe(pipefd);
	while (i < (ac - 1))
	{
		id[i_id] = fork();
		if (id[i_id] == 0)
		{
			cmd_arg = get_cmd_args(av[i]);
			printf("cmd-[%s]\n", cmd_arg[0]);
			close(pipefd[0]);
			cmd = ft_strjoin(cmd_arg[0], "\n");
			write(pipefd[1], cmd, ft_strlen(cmd) + 1);
			free(cmd);
			close(pipefd[1]);
			execve(cmd_arg[0], cmd_arg, env);
			exit(1);
		}
		++i;
		++i_id;
	}
	i_id = 0;
	close(pipefd[1]);
	while (i_id < id_len)
	{
		waitpid(id[i_id], &return_child, WUNTRACED);
		// waitpid(0, &return_child, WUNTRACED);
		get_next_line(pipefd[0], &test);
		printf("return-[%s]\n", test);
		free(test);
		++i_id;
	}
	close(pipefd[0]);
	free(id);
}

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
