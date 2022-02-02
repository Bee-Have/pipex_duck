/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_args.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 16:12:37 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/02 18:46:28 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	parsing_args(int ac, char **av)
{
	if (ft_strcmp(av[1], "here_doc") == 0)
		return (error_manager(ERNO_ARGS_NO_BONUS, NULL));
	if (ac <= 1)
		return (error_manager(ERNO_NO_ARGS, NULL));
	if (ac < 5)
		return (error_manager(ERNO_ARGS_NBR_LESS, NULL));
	if (ac > 5)
		return (error_manager(ERNO_ARGS_NBR_MORE, NULL));
	return (EXIT_SUCCESS);
}

#else

int	parsing_args(int ac, char **av)
{
	int	offset;

	offset = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		offset = 1;
	if (ac <= 1)
		return (error_manager(ERNO_NO_ARGS, NULL));
	if (ac < (5 + offset))
		return (error_manager(ERNO_ARGS_NBR_LESS, NULL));
	return (EXIT_SUCCESS);
}

#endif
