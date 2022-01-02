/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:04:12 by user42            #+#    #+#             */
/*   Updated: 2022/01/02 10:13:38 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	parsing_args(int bonus, int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;
	int	offset;

	if (bonus == 0)
		offset = 2;
	else if (bonus == 1)
		offset = 3;
	if ((ac - offset) < 1 || (bonus == 0 && ac < 4) || (bonus == 1 && ac < 5))
		return (print_error(ERNO_ARGS_NBR));
	if (bonus == 0 && ft_strcmp(av[1], "here_doc"))
		return (print_error(ERNO_BONUS));
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
}
