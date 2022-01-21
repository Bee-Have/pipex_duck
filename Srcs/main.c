/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:50:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/21 18:23:11 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		i;
	char	**cmds;

	i = 0;
	if (parsing_manager(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1], O_WRONLY | O_TRUNC);
	cmds = (char **)malloc(((ac - 3) + 1) * sizeof(char *));
	if (!cmds)
		return (EXIT_FAILURE);
	cmds[ac - 3] = NULL;
	while (i < (ac - 3))
	{
		cmds[i] = ft_strdup(av[i + 2]);
		++i;
	}
	if (fork_manager(files, cmds, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	close(files[0]);
	close(files[1]);
	return (EXIT_SUCCESS);
}

#else
//here : file[0]=infile | file[1]=outfile | file[2]=stdin
int	main(int ac, char **av, char *env[])
{
	int		files[3];
	char	**cmds;
	char	**here_doc;

	here_doc = NULL;
	files[0] = NO_INFILE;
	files[2] = dup(STDIN_FILENO);
	if (parsing_manager(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = get_lines_limiter(av[2]);
	if (here_doc == NULL)
		files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1], O_WRONLY | O_APPEND);
	cmds = make_av_cmds(ac, av);
	if (here_doc)
		write_here_doc_file(here_doc);
	if (fork_manager(files, cmds, env) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (!here_doc)
		close(files[0]);
	close(files[1]);
	close(files[2]);
	return (EXIT_SUCCESS);
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
		write(STDIN_FILENO, prefix, ft_strlen(prefix));
		get_next_line(0, &line);
		result = ft_add_tab(result, line);
	}
	free(line);
	free(prefix);
	return (result);
}

void	write_here_doc_file(char **here_doc)
{
	int	i;

	i = 0;
	while (here_doc[i])
	{
		write(STDIN_FILENO, here_doc[i], ft_strlen(here_doc[i]));
		write(STDIN_FILENO, "\n", 1);
		++i;
	}
	ft_freetab(here_doc);
}

#endif
