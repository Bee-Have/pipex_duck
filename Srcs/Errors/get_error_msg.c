/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_error_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 14:40:21 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/08 15:47:11 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_error_args(int erno)
{
	char	*error;

	error = NULL;
	if (erno == ERNO_NAME)
		error = ft_strdup("Wrong name for executable");
	else if (erno == ERNO_NO_ARGS)
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
	char	*tmp;
	char	*error;

	if (erno == ERNO_FILE)
		error = ft_strdup(": No such file or directory");
	else if (erno == ERNO_PERMISSION)
	{
		error = ft_strdup(": Permission denied");
		*err = 126;
	}
	else if (erno == ERNO_PATH)
	{
		tmp = ft_strjoin("Command \'", str);
		error = ft_strjoin(tmp, "\' not found");
		free(tmp);
		res = ft_strdup(error);
		*err = 127;
	}
	if (erno != ERNO_PATH)
		res = ft_strjoin(str, error);
	free(error);
	return (res);
}
