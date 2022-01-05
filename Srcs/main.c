/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:02:36 by user42            #+#    #+#             */
/*   Updated: 2022/01/05 15:54:11 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Here, files[0] == infile (av[1])
//Here, files[1] == outfile (av[ac - 1])
int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		i;
	char	**here_doc;
	char	**cmds;

	//parse
	here_doc = NULL;
	if (parsing_manager(ac, av) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	//check for here_doc
	//if here_doc -> send to other function
	if (ft_strcmp(av[1], "here_doc") == 0)
		here_doc = get_here_doc(av[2]);
	i = 0;
	//open fd infile/outfile
	files[1] = open(av[ac - 1], O_WRONLY | O_TRUNC);
	files[0] = open(av[1], O_RDONLY);
	//create new 'av' with just cmds
	cmds = (char **)malloc(((ac - 3) + 1) * sizeof(char *));
	if (!cmds)
		return(EXIT_FAILURE);
	cmds[ac - 3] = NULL;
	while(i < (ac - 3))
	{
		cmds[i] = ft_strdup(av[i + 2]);
		++i;
	}
	//function call for pipe here
	//function call for fork
	fork_cmds(files, cmds, env);
	close(files[0]);
	close(files[1]);
	return (EXIT_SUCCESS);
}
