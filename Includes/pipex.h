/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:21 by user42            #+#    #+#             */
/*   Updated: 2021/12/16 18:39:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft.h"
# include "ft_get_file.h"

# define PATH_OK 1
# define PATH_KO -1

# define ERNO_ARGS_NBR 0
# define ERNO_INFILE 1
# define ERNO_OUTFILE 2
# define ERNO_PATH 3

int		main(int ac, char **av, char *env[]);
char	**get_cmd_args(char *cmd);

int		parsing_args(int ac, char **av);
int		check_cmd_env(char **cmd, char *env[]);


#endif