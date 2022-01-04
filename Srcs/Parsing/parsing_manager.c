/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:04:12 by user42            #+#    #+#             */
/*   Updated: 2022/01/04 16:47:35 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing_manager(int bonus, int ac, char **av)
{
	//check for infile/outfile
	if (parsing_files(bonus, ac, av) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (bonus == 0)
	{
		//check for args NO BONUS
		if (parsing_args_nbr(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (bonus == 1)
	{
		//check for args BONUS
		if (parsing_args_nbr_bonus(ac, av) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	parsing_files(int bonus, int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	ret_infile = open(av[1 + bonus], O_RDONLY);
	ret_outfile = open(av[ac - 1], O_RDWR);
	if(ret_infile == -1)
	{
		if (ret_outfile != -1)
			close(ret_outfile);
		return (print_error(ERNO_INFILE));
	}
	if (ret_outfile == -1)
	{
		if (ret_infile != -1)
			close(ret_infile);
		return (print_error(ERNO_OUTFILE));
	}
	return (EXIT_SUCCESS);
}

int	parsing_args_nbr(int ac, char **av)
{
	//if no args -> error NO_ARGS
	if (ac == 1)
		return (print_error(ERNO_NO_ARGS));
	//if args < 4 -> error NO_ARGS
	if (ac < 5)
		return (print_error(ERNO_ARGS_NBR_LESS));
	//if args > 4 -> error TO_MANY_ARGS
	if (ac > 5)
		return (print_error(ERNO_ARGS_NBR_MORE));
	//if av[1] == here_doc -> error BONUS_FOR_NOBONUS
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (print_error(ERNO_ARGS_NO_BONUS));
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
		return (print_error(ERNO_BONUS_NO_ARGS));
	//if args < 4 + offset -> error NO ARGS
	if (ac < (5 + offset))
		return (print_error(ERNO_BONUS_ARGS_NBR));
	return (EXIT_SUCCESS);
}
