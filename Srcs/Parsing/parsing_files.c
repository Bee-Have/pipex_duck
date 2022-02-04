/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:13:18 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/04 16:16:27 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

//here: ret_infile[0]=does file exists ?
//here: ret_infile[0]=can you read file ?
int	parsing_files(int ac, char **av)
{
	int	ret_infile[2];
	int	ret_r_outfile;
	int	ret_w_outfile;
	int	ret_f_outfile;

	ret_infile[0] = access(av[1], F_OK);
	if (ret_infile[0] == -1)
		error_manager(ERNO_INFILE, av[1]);
	ret_infile[1] = access(av[1], R_OK);
	if (ret_infile[0] != -1 && ret_infile[1] == -1)
		error_manager(ERNO_PERMISSION, av[1]);
	ret_r_outfile = access(av[ac - 1], R_OK);
	ret_w_outfile = access(av[ac - 1], W_OK);
	ret_f_outfile = access(av[ac - 1], F_OK);
	if ((ret_r_outfile == -1 || ret_w_outfile == -1) && ret_f_outfile != -1)
		return (error_manager(ERNO_PERMISSION, av[ac - 1]));
	return (EXIT_SUCCESS);
}

#else

//here: ret_infile[0]=does file exists ?
//here: ret_infile[0]=can you read file ?
int	parsing_files(int ac, char **av)
{
	int	ret_infile[2];
	int	ret_r_outfile;
	int	ret_w_outfile;
	int	ret_f_outfile;

	if (ft_strcmp(av[1], "here_doc") == 0)
		ret_infile[0] = NO_INFILE;
	else
	{
		ret_infile[0] = access(av[1], F_OK);
		if (ret_infile[0] == -1)
			error_manager(ERNO_INFILE, av[1]);
		ret_infile[1] = access(av[1], R_OK);
		if (ret_infile[0] != -1 && ret_infile[1] == -1)
			error_manager(ERNO_PERMISSION, av[1]);
	}
	ret_r_outfile = access(av[ac - 1], R_OK);
	ret_w_outfile = access(av[ac - 1], W_OK);
	ret_f_outfile = access(av[ac - 1], F_OK);
	if ((ret_r_outfile == -1 || ret_w_outfile == -1) && ret_f_outfile != -1)
		return (error_manager(ERNO_PERMISSION, av[ac - 1]));
	return (EXIT_SUCCESS);
}

#endif
