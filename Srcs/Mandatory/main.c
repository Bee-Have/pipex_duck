/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:50:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/10 17:46:24 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		i;
	char	**cmds;

	//check of parsing
	i = 0;
	//open fds
	files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1], O_WRONLY | O_APPEND);
	//make new av with only cmds
	cmds = (char **)malloc(((ac - 3) + 1) * sizeof(char *));
	if (!cmds)
		return (EXIT_FAILURE);
	cmds[ac - 3] = NULL;
	while (i < (ac - 3))
	{
		cmds[i] = ft_strdup(av[i + 2]);
		++i;
	}
	//call function to pipe/fork
	if (fork_manager(files, cmds, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	//close all fds
	close(files[0]);
	close(files[1]);
	return (EXIT_SUCCESS);
}

#else
int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		pipefd[2];
	char	*cmds;
	char	**here_doc;

	here_doc = NULL;
	if (parsing_manager(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = get_lines_limiter(av[2]);
	if (here_doc == NULL)
		files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1],O_WRONLY | O_TRUNC);
	cmds = make_av_cmds(ac, av);
	pipe(pipefd);
	if (here_doc)
		write_here_doc_file(&pipefd, &files, here_doc);
	if (fork_manager(pipefd, files, cmds, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!here_doc)
		close(files[0]);
	close(files[1]);
	return (EXIT_SUCCESS);
}

char	**get_lines_limiter(char *limiter)
{
	char	*line;
	char	*prefix;
	char	**result;

	line = NULL;
	result = NULL;
	prefix = ft_strdup("pipe here_doc> ");
	while (ft_strcmp(line, limiter) == 1)
	{
		free(line);
		write(1, prefix, ft_strlen(prefix));
		get_next_line(0, &line);
		result = ft_add_tab(result, line);
	}
	free(line);
	free(prefix);
	return (result);
}

char	**make_av_cmds(int ac, char **av)
{
	int		i;
	int		modifier;
	char	**cmds;

	i = 0;
	modifier = 3;
	if (ft_strcmp(av[1], "here_doc") == 0)
		modifier = 4;
	cmds = (char **)malloc(((ac - modifier) + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmds[ac -modifier] = NULL;
	while (i < (ac - modifier))
	{
		cmds[i] = ft_strdup(av[i + (modifier - 1)]);
		++i;
	}
	return (cmds);
}

void	write_here_doc_file(int (*pipefd)[2], int (*files)[2], char **here_doc)
{
	int	i;

	i = 0;
	while (here_doc[i])
	{
		write((*pipefd)[1], here_doc[i], ft_strlen(here_doc[i]));
		write((*pipefd)[1], "\n", 1);
		++i;
	}
	ft_freetab(here_doc);
	(*files)[0] = (*pipefd)[0];
}

#endif