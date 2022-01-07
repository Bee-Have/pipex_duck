/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:21 by user42            #+#    #+#             */
/*   Updated: 2022/01/07 15:20:46 by amarini-         ###   ########.fr       */
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

# define ERNO_NAME 0
# define ERNO_INFILE 1
# define ERNO_OUTFILE 2
# define ERNO_NO_ARGS 3
# define ERNO_ARGS_NBR_LESS 4
# define ERNO_ARGS_NBR_MORE 5
# define ERNO_ARGS_NO_BONUS 6
# define ERNO_BONUS_NO_ARGS 7
# define ERNO_BONUS_ARGS_NBR 8
# define ERNO_PATH 9

//MAIN
int		main(int ac, char **av, char *env[]);

//MAIN ARGS MANAGER
char	**get_cmd_args(char *cmd);
int		check_cmd_env(char **cmd, char *env[]);

//PARSING ARGS
int		parsing_manager(int ac, char **av);
int		parsing_files(int bonus, int ac, char **av);
int		parsing_args_nbr(int ac, char **av);
int		parsing_args_nbr_bonus(int ac, char **av);

//BONUS
char	**get_here_doc(char *limiter);
char	**here_doc_checker(int ac, char **av, int (*pipefd)[2], int (*files)[2]);
char	**make_av_cmds(int modifier, int ac, char **av);

//FORKING
int		fork_cmds(int pipefd[2], int files[2], char **cmds, char *env[]);
void	wait_for_children(/*pid_t *children,*/ int size);
void	dup2_children(int max, int index, int pipefd[2], int files[2]);

//ERROR MANAGEMENT
int		error_manager(int erno);
// void	singular_errors(int erno);
// void	mandatory_errors(int erno);
// void	bonus_errors(int erno);

#endif