/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:31:41 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/02 19:01:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_manager(int erno, char *str)
{
	int		err;
	char	*msg;
	char	*error;
	char	*erno_str;

	erno_str = ft_itoa(errno);
	write(2, erno_str, ft_strlen(erno_str));
	write(2, "\n", 1);
	if (erno == ERNO_NAME || erno == ERNO_INFILE || erno == ERNO_EMPTY_CMD
		|| erno == ERNO_PATH)
		msg = get_error_misc(erno, str, &err);
	else if (erno == ERNO_NO_ARGS || erno == ERNO_ARGS_NBR_LESS
		|| erno == ERNO_ARGS_NBR_MORE || erno == ERNO_ARGS_NO_BONUS)
		msg = get_error_args(erno);
	error = add_prefix_sufix(msg);
	(void)str;
	free(msg);
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
	return (err);
}
