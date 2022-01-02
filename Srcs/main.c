/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:02:36 by user42            #+#    #+#             */
/*   Updated: 2022/01/02 10:13:14 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//Here, files[0] == infile (av[1])
//Here, files[1] == outfile (av[ac - 1])
int	main(int ac, char **av, char *env[])
{
	int		files[2];
	int		bonus;
	int		i;
	char	**cmds;

	//check program name
	if (ft_strcmp(av[0], "./pipex"))
		bonus = 0;
	else if (ft_strcmp(av[0], "./pipex_bonus"))
		bonus = 1;
	else
		return(print_error(ERNO_NAME));
	//parse
	if (parsing_args(bonus, ac, av) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	i = 0;
	//open fd infile/outfile
	files[0] = open(av[1], O_RDONLY);
	files[1] = open(av[ac - 1], O_WRONLY | O_TRUNC);
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
	// ft_print_tab(cmds);
	//function call for fork
	fork_cmds(files, cmds, env);
	close(files[0]);
	close(files[1]);
	return (EXIT_SUCCESS);
}
