/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:12:37 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/10 16:26:49 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS
int	parsing_args(int ac, char **av)
{
	//if there is here_doc -> doing bonus with ./pipex :(
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (error_manager(ERNO_ARGS_NO_BONUS));
	//if no arg :(
	if (ac == 1)
		return (error_manager(ERNO_NO_ARGS));
	//if args are incomplete :(
	if (ac < 5)
		return (error_manager(ERNO_ARGS_NBR_LESS));
	//if args > 5 -> multipipe not suported by ./pipex :(
	if (ac > 5)
		return (error_manager(ERNO_ARGS_NBR_MORE));
	//if none triggers SUCCESS
	return (EXIT_SUCCESS);
}

#else
int	parsing_args(int ac, char **av)
{
	int	offset;

	offset = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		offset = 1;
	if (ac == 1)
		return (error_manager(ERNO_NO_ARGS));
	if (ac < (5 + offset))
		return (error_manager(ERNO_ARGS_NBR_LESS));
	return (EXIT_SUCCESS);
}

#endif
