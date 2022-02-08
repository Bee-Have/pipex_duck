/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 14:00:12 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/08 17:51:35 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

int	parsing_manager(int ac, char **av)
{
	int	files_ret;

	if (ft_strcmp(av[0], "./pipex") == 1)
		return (error_manager(ERNO_NAME, NULL));
	files_ret = parsing_files(ac, av);
	if (files_ret != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

#else

int	parsing_manager(int ac, char **av)
{
	int	files_ret;

	if (ft_strcmp(av[0], "./pipex_bonus") == 1)
		return (error_manager(ERNO_NAME, NULL));
	files_ret = parsing_files(ac, av);
	if (files_ret != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

#endif
