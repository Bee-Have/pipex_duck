/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:40:21 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/02 19:02:34 by amarini-         ###   ########.fr       */
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

char	*get_error_misc(int erno, char *str, int *err)
{
	char	*res;
	char	*error;

	error = NULL;
	if (erno == ERNO_NAME)
		error = ft_strdup("Wrong name for executable");
	else if (erno == ERNO_INFILE)
	{
		if (errno == 2)
			error = ft_strdup(": No such file or directory");
		if (errno == 13)
			error = ft_strdup(": Permission denied");
	}
	else if (erno == ERNO_EMPTY_CMD)
	{
		error = ft_strdup("One of the commands is empty, please "
				"enter existing command");
		*err = 127;
	}
	else if (erno == ERNO_PATH)
	{
		if (errno == 2)
			error = ft_strdup(": command not found");
		*err = 127;
	}
	res = ft_strjoin(str, error);
	return (res);
}
