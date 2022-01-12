/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:40:21 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/12 14:41:42 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_error_args(int erno)
{
	char	*error;

	error = NULL;
	if (erno == ERNO_NO_ARGS)
		error = ft_strdup("No arguments after executable");
	else if (erno == ERNO_ARGS_NBR_LESS)
		error = ft_strdup("List of arguments is incomplete");
	else if (erno == ERNO_ARGS_NBR_MORE)
		error = ft_strdup("Too many arguments (For multi pipe feature, "
							"please use 'make bonus')");
	else if (erno == ERNO_ARGS_NO_BONUS)
		error = ft_strdup("This executable does not support bonuses "
						"(please use 'make bonus' for this feature)");
	return (error);
}

char	*get_error_misc(int erno)
{
	char	*error;

	if (erno == ERNO_NAME)
		error = ft_strdup("Wrong name for executable");
	else if (erno == ERNO_INFILE)
		error = ft_strdup("Path of infile is either incorrect or inexistant");
	else if (erno == ERNO_OUTFILE)
		error = ft_strdup("Path of outfile is either incorrect or inexistant");
	else if (erno == ERNO_EMPTY_CMD)
		error = ft_strdup("One of the commands is empty, please "
							"enter existing command");
	else if (erno == ERNO_PATH)
		error = ft_strdup("Path for one of the commands does not exist, please"
				" check all the commands exist or they have an existing path");
	return (error);
}
