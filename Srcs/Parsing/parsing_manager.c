/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:04:12 by user42            #+#    #+#             */
/*   Updated: 2022/01/10 16:27:42 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing_manager_old(int ac, char **av)
{
	//check program name
	if (ft_strcmp(av[0], "./pipex") == 1
		&& ft_strcmp(av[0], "./pipex_bonus") == 1)
		return(error_manager(ERNO_NAME));
	if (ft_strcmp(av[0], "./pipex") == 0)
	{
		//check for args NO BONUS
		if (parsing_args_nbr(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (ft_strcmp(av[0], "./pipex_bonus") == 0)
	{
		//check for args BONUS
		if (parsing_args_nbr_bonus(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	//check for infile/outfile
	if (parsing_files(ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	parsing_files(int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	if (ft_strcmp(av[1], "here_doc") == 0)
		ret_infile = 0;
	else
		ret_infile = open(av[1], O_RDONLY);
	ret_outfile = open(av[ac - 1], O_RDWR);
	if(ret_infile == -1)
	{
		if (ret_outfile != -1)
			close(ret_outfile);
		return (error_manager(ERNO_INFILE));
	}
	if (ret_outfile == -1)
	{
		if (ret_infile != -1)
			close(ret_infile);
		return (error_manager(ERNO_OUTFILE));
	}
	return (EXIT_SUCCESS);
}

int	parsing_args_nbr(int ac, char **av)
{
	//if av[1] == here_doc -> error BONUS_FOR_NOBONUS
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (error_manager(ERNO_ARGS_NO_BONUS));
	//if no args -> error NO_ARGS
	if (ac == 1)
		return (error_manager(ERNO_NO_ARGS));
	//if args < 4 -> error NO_ARGS
	if (ac < 5)
		return (error_manager(ERNO_ARGS_NBR_LESS));
	//if args > 4 -> error TO_MANY_ARGS
	if (ac > 5)
		return (error_manager(ERNO_ARGS_NBR_MORE));
	return (EXIT_SUCCESS);
}

int	parsing_args_nbr_bonus(int ac, char **av)
{
	int	offset;

	offset = 0;
	//make offset if here_doc
	if (ft_strcmp(av[1], "here_doc") == 0)
		offset = 1;
	//if no args -> error NO_ARGS
	if (ac == 1)
		return (error_manager(ERNO_NO_ARGS));
	//if args < 4 + offset -> error NO ARGS
	if (ac < (5 + offset))
		return (error_manager(ERNO_ARGS_NBR_LESS));
	return (EXIT_SUCCESS);
}
