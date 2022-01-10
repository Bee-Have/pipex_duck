/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:13:18 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/10 16:23:36 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
int	parsing_files(int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	//open infile && outfile
	ret_infile = open(av[1], O_RDONLY);
	ret_outfile = open(av[ac - 1], O_RDONLY);
	//if infile open fails :(
	if (ret_infile == -1)
	{
		//if outfile succeded -> try to close it
		if (ret_outfile != -1)
			close(ret_outfile);
		return (error_manager(ERNO_INFILE));
	}
	//if outfile open fails :(
	if (ret_outfile == -1)
	{
		//if infile succeded -> try to close it
		if (ret_infile != -1)
			close(ret_infile);
		return (error_manager(ERNO_OUTFILE));
	}
	//if none triggers SUCCESS
	return (EXIT_SUCCESS);
}

#else
int	parsing_files(int ac, char **av)
{
	int	ret_infile;
	int	ret_outfile;

	if (ft_strcmp(av[1], "here_doc") == 0)
		ret_infile = 0;
	else
		ret_infile = open(av[1], O_RDONLY);
	ret_outfile = open(av[ac - 1], O_RDWR);
	if (ret_infile == -1)
	{
		if (ret_outfile != -1)
			close(ret_outfile);
		return (error_manager(ERNO_INFILE));
	}
	if (ret_outfile == -1)
	{
		if (ret_infile != -1 && ret_infile != 0)
			close(ret_infile);
		return(error_manager(ERNO_OUTFILE));
	}
	return (EXIT_SUCCESS);
}

#endif