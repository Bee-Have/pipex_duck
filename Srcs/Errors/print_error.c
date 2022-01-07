/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:08:43 by user42            #+#    #+#             */
/*   Updated: 2022/01/05 13:49:16 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_manager(int erno)
{
	//This is temporary
	// if (erno != -1)
	// {
	// 	ft_putstr("ERROR : [");
	// 	ft_putnbr(erno);
	// 	ft_putstr("]\n");
	// }
	//For : 0 -> print error + exemple of names
	//For : 1 2 -> print error + exemple of path
	//For : 9 -> print error
	//For : 3 to 6 -> print error + exemple of how to compile
	//For : 7 to 8 -> print error + exemple of how to compile
	if (erno == ERNO_NAME || erno == ERNO_INFILE || erno == ERNO_OUTFILE 
		|| erno == ERNO_PATH)
		singular_errors(erno);
	else if (erno == ERNO_NO_ARGS || erno == ERNO_ARGS_NBR_LESS
		|| erno == ERNO_ARGS_NBR_MORE || erno == ERNO_ARGS_NO_BONUS)
		mandatory_errors(erno);
	else if (erno == ERNO_BONUS_NO_ARGS || erno == ERNO_BONUS_ARGS_NBR)
		bonus_errors(erno);
	return (EXIT_FAILURE);
}

//SINGULAR errors
void	singular_errors(int erno)
{
	char	*prefix;
	char	*ex_names;
	char	*ex_path;
	char	*msg;

	msg = "\n";
	prefix = ft_strdup("Error : ");
	ex_names = ft_strdup("Usage : 'pipex' || 'pipex_bonus'\n");
	ex_path = ft_strdup("Usage : file_name\n");
	//For : 0 -> print error + exemple of names
	//For : 1 2 -> print error + exemple of path
	//For : 9 -> print
	if (erno == ERNO_NAME)
	{
		msg = ft_strjoin(prefix, "Wrong name for executable\n");
		ft_putstr(msg);
		ft_putstr(ex_names);
	}
	else if (erno == ERNO_INFILE || erno == ERNO_OUTFILE)
	{
		if (erno == ERNO_INFILE)
			msg = ft_strjoin(prefix, "Infile path does not exist\n");
		else if (erno == ERNO_OUTFILE)
			msg = ft_strjoin(prefix, "Outfile path does not exist\n");
		ft_putstr(msg);
		ft_putstr(ex_path);
	}
	else if (erno == ERNO_PATH)
	{
		msg = ft_strjoin(prefix, "Command path does not exist\n");
		ft_putstr(msg);
	}
}

//MANDATORY erros
void	mandatory_errors(int erno)
{
	char	*prefix;
	char	*error;
	char	*msg;
	char	*usage;

	error = "\n";
	prefix = ft_strdup("Error : ");
	usage = ft_strdup("Usage : [./]pipex infile cmd1 cmd2 outfile\n");
	//For : 3 to 6 -> print error + exemple of how to compile
	if (erno == ERNO_NO_ARGS)
		error = ft_strdup("No arguments after executable\n");
	else if (erno == ERNO_ARGS_NBR_LESS)
		error = ft_strdup("List of arguments is incomplete\n");
	else if (erno == ERNO_ARGS_NBR_MORE)
		error = ft_strdup("Too many arguments\n");
	else if (erno == ERNO_ARGS_NO_BONUS)
		error = ft_strdup("This executable does not support bonuses\n");
	msg = ft_strjoin(prefix, error);
	ft_putstr(msg);
	ft_putstr(usage);
}

//BONUS errors
void	bonus_errors(int erno)
{
	char	*prefix;
	char	*error;
	char	*msg;
	char	*usage;

	error = "\n";
	prefix = ft_strdup("Error : ");
	usage = ft_strdup("Usage : [./]pipex_bonus {[here_doc 'LIMITER'] ||"
						" [infile]} cmd1 cmd2 [cmd3 ect...] outfile\n");
	//For : 7 to 8 -> print error + exemple of how to compile
	if (erno == ERNO_BONUS_NO_ARGS)
		error = ft_strdup("No arguments after executable\n");
	else if (erno == ERNO_BONUS_ARGS_NBR)
		error = ft_strdup("List of arguments incomplete\n");
	msg = ft_strjoin(prefix, error);
	ft_putstr(msg);
	ft_putstr(usage);
}
