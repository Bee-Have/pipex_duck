/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:21 by user42            #+#    #+#             */
/*   Updated: 2021/12/25 19:48:27 by user42           ###   ########.fr       */
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

//MAIN
int		main(int ac, char **av, char *env[]);

//MAIN ARGS MANAGER
char	**get_cmd_args(char *cmd);
int		check_cmd_env(char **cmd, char *env[]);

//PARSING ARGS
int		parsing_args(int ac, char **av);

//FORKING
int		fork_cmds(int files[2], char **cmds, char *env[]);
void	wait_for_children(/*pid_t *children,*/ int size);
void	dup2_children(int max, int index, int pipefd[2], int files[2]);

//ERROR MANAGEMENT
int		print_error(int erno);

#endif