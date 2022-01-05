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
	//For : 0 -> print error + exemple of names
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

}

//MANDATORY erros
void	mandatory_errors(int erno)
{

}

//BONUS errors
void	bonus_errors(int erno)
{

}
