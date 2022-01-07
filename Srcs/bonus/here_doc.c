/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 15:46:53 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/07 16:40:40 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**here_doc_checker(int ac, char **av, int (*pipefd)[2], int (*files)[2])
{
	int		i;
	int		modifier;
	char	**cmds;
	char	**here_doc;

	i = 0;
	modifier = 3;
	here_doc = NULL;
	//first, get heredoc
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = get_here_doc(av[2]);
	//open infile && outfile
	if (here_doc == NULL)
	{
		(*files)[0] = open(av[1], O_RDONLY);
		(*files)[1] = open(av[ac - 1], O_WRONLY | O_TRUNC);
	}
	else
		(*files)[1] = open(av[ac - 1], O_WRONLY | O_APPEND);
	//make cmds for fork
	if (here_doc != NULL)
		modifier = 4;
	cmds = make_av_cmds(modifier, ac, av);
	//pipe
	pipe(*pipefd);
	if (here_doc != NULL)
	{
		while (here_doc[i])
		{
			write((*pipefd)[0], here_doc[i], ft_strlen(here_doc[i]));
			write((*pipefd)[0], "\n", 1);
			++i;
		}
		ft_freetab(here_doc);
		*files[0] = (*pipefd)[0];
	}
	return (cmds);
}

char	**make_av_cmds(int modifier, int ac, char **av)
{
	int		i;
	char	**cmds;

	i = 0;
	cmds = (char **)malloc(((ac - modifier) + 1) * sizeof(char *));
	if (!cmds)
		return (NULL);
	cmds[ac - modifier] = NULL;
	while (i < (ac - modifier))
	{
		cmds[i] = ft_strdup(av[i + (modifier - 1)]);
		++i;
	}
	return (cmds);
}

char	**get_here_doc(char *limiter)
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
