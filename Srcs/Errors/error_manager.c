/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:31:41 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/08 15:47:11 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_manager(int erno, char *str)
{
	int			err;
	char		*msg;
	char		*error;

	err = 2;
	if (erno == ERNO_FILE || erno == ERNO_PATH || erno == ERNO_PERMISSION)
		msg = get_error_misc(erno, str, &err);
	else if (erno == ERNO_NAME || erno == ERNO_NO_ARGS
		|| erno == ERNO_ARGS_NBR_LESS || erno == ERNO_ARGS_NBR_MORE
		|| erno == ERNO_ARGS_NO_BONUS)
		msg = get_error_args(erno);
	error = add_prefix_sufix(msg);
	(void)str;
	free(msg);
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
	return (err);
}
