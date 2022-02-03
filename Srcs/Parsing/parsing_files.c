/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:13:18 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/03 13:54:21 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	parsing_files(int ac, char **av)
{
	int	ret_infile;
	int	ret_r_outfile;
	int	ret_w_outfile;
	int	ret_f_outfile;

	ret_infile = access(av[1], F_OK);
	if (ret_infile == -1)
		return (error_manager(ERNO_INFILE, av[1]));
	ret_infile = access(av[1], R_OK);
	if (ret_infile == -1)
		return (error_manager(ERNO_PERMISSION, av[1]));

	ret_r_outfile = access(av[ac - 1], R_OK);
	ret_w_outfile = access(av[ac - 1], W_OK);
	ret_f_outfile = access(av[ac - 1], F_OK);
	if ((ret_r_outfile == -1 || ret_w_outfile == -1) && ret_f_outfile != -1)
		return (error_manager(ERNO_PERMISSION, av[ac - 1]));
	return (EXIT_SUCCESS);
}

#else

int	parsing_files(int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	if (ft_strcmp(av[1], "here_doc") == 0)
		ret_infile = NO_INFILE;
	else
		ret_infile = open(av[1], O_RDONLY);
	ret_outfile = open(av[ac - 1], O_RDWR);
	if (ret_infile == -1)
	{
		if (ret_outfile != -1)
			close(ret_outfile);
		return (error_manager(ERNO_INFILE, av[1]));
	}
	if (ret_infile != NO_INFILE)
		close(ret_infile);
	close(ret_outfile);
	return (EXIT_SUCCESS);
}

#endif
