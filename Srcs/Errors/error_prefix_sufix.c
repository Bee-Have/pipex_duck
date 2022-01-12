/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_prefix_sufix.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 15:24:34 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/12 15:33:06 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifndef BONUS

char	*add_prefix_sufix(char *error)
{
	char	*result;
	char	*prefix;
	char	*sufix;
	char	*tmp;

	prefix = ft_strdup("Error : ");
	sufix = ft_strdup("\nUsage : [./]pipex infile cmd1 cmd2 outfile\n");
	tmp = ft_strjoin(prefix, error);
	result = ft_strjoin(tmp, sufix);
	free(prefix);
	free(sufix);
	free(tmp);
	return (result);
}

#else

char	*add_prefix_sufix(char *error)
{
	char	*result;
	char	*prefix;
	char	*sufix;
	char	*tmp;

	prefix = ft_strdup("Error : ");
	sufix = ft_strdup("\nUsage : [./]pipex_bonus {[here_doc 'LIMITER'] "
						"|| infile} cmd1 cmd2 [cmd3 ect...] outfile\n");
	tmp = ft_strjoin(prefix, error);
	result = ft_strjoin(tmp, sufix);
	free(prefix);
	free(sufix);
	free(tmp);
	return (result);
}

#endif
