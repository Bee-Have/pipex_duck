/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 18:08:43 by user42            #+#    #+#             */
/*   Updated: 2021/12/08 18:29:12 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	print_error(int erno)
{
	//look how to do enum because dis is bad
	//add usage if problem comes from parsing args
	if (erno == ERNO_ARGS_NBR)
		ft_putstr("Error: Wrong number of arguments\n");
	else if (erno == ERNO_INFILE)
		ft_putstr("Error: Wrong path for infile\n");
	else if (erno == ERNO_OUTFILE)
		ft_putstr("Error: Wrong path for outfile\n");
	return (EXIT_FAILURE);
}
