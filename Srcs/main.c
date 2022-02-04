/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 13:50:36 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/04 19:10:55 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		i;
	char	**cmds;
	int		ret;

	i = 0;
	if (parsing_manager(ac, av) != EXIT_SUCCESS)
		ret = 0;
	files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	cmds = (char **)malloc(((ac - 3) + 1) * sizeof(char *));
	if (!cmds)
		return (EXIT_FAILURE);
	cmds[ac - 3] = NULL;
	while (i < (ac - 3))
	{
		cmds[i] = ft_strdup(av[i + 2]);
		++i;
	}
	ret = fork_manager(files, cmds, env);
	ft_freetab(cmds);
	close(files[0]);
	close(files[1]);
	return (ret);
}

#else

//here : file[0]=infile | file[1]=outfile | file[2]=stdin
int	main(int ac, char **av, char *env[])
{
	int		ret;
	int		files[3];
	char	**cmds;

	files[0] = NO_INFILE;
	files[2] = dup(STDIN_FILENO);
	if (parsing_manager(ac, av) == EXIT_FAILURE)
		ret = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		files[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_APPEND, 0777);
	else
	{
		files[0] = open(av[1], O_RDONLY);
		files[1] = open(av[ac - 1], O_RDWR | O_CREAT | O_TRUNC, 0777);
	}
	cmds = make_av_cmds(ac, av);
	ret = fork_manager(files, &cmds, env);
	ft_freetab(cmds);
	close(files[1]);
	close(files[2]);
	return (ret);
}

char	**make_av_cmds(int ac, char **av)
{
	int		i;
	int		modifier;
	char	**cmds;

	i = 0;
	modifier = 3;
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

#endif
