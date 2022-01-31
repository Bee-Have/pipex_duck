/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 18:31:41 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/31 12:29:56 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	error_manager(int erno)
{
	char	*msg;
	char	*error;

	if (erno == ERNO_NAME || erno == ERNO_INFILE || erno == ERNO_OUTFILE
		|| erno == ERNO_EMPTY_CMD || erno == ERNO_PATH)
		msg = get_error_misc(erno);
	else if (erno == ERNO_NO_ARGS || erno == ERNO_ARGS_NBR_LESS
		|| erno == ERNO_ARGS_NBR_MORE || erno == ERNO_ARGS_NO_BONUS)
		msg = get_error_args(erno);
	error = add_prefix_sufix(msg);
	free(msg);
	write(STDERR_FILENO, error, ft_strlen(error));
	free(error);
	return (EXIT_FAILURE);
}
