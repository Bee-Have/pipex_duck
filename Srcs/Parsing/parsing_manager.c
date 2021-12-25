/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:04:12 by user42            #+#    #+#             */
/*   Updated: 2021/12/25 19:08:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parsing_args(int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	if ((ac - 2) < 1 || ac == 1)
		return (print_error(ERNO_ARGS_NBR));
	ret_infile = open(av[1], O_RDONLY);
	ret_outfile = open(av[(ac - 1)], O_RDONLY);
	if (ret_infile == -1)
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
