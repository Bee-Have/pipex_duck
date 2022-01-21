/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:21 by user42            #+#    #+#             */
/*   Updated: 2022/01/21 18:28:58 by amarini-         ###   ########.fr       */
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

# define NO_INFILE -2

# define ERNO_NAME 0
# define ERNO_INFILE 1
# define ERNO_OUTFILE 2
# define ERNO_NO_ARGS 3
# define ERNO_ARGS_NBR_LESS 4
# define ERNO_ARGS_NBR_MORE 5
# define ERNO_ARGS_NO_BONUS 6
# define ERNO_EMPTY_CMD 7
# define ERNO_PATH 8

//MAIN
int		main(int ac, char **av, char *env[]);

# ifdef BONUS
char	**get_lines_limiter(char *limiter);
char	**make_av_cmds(int ac, char **av);
void	write_here_doc_file(char **here_doc);
# endif

//PARSING
int		parsing_manager(int ac, char **av);
int		parsing_args(int ac, char **av);
int		parsing_files(int ac, char **av);

//FORK
# ifndef BONUS
int		fork_manager(int files[2], char **cmds, char *env[]);
int		fork_cmds(pid_t *child, int files[2], char **cmds, char *env[]);
void	dup2_children(int index, int pipefd[2], int files[2]);
# else
int		fork_manager(/*int pipefd[2], */int files[3], char **cmds, char *env[]);
int		fork_cmds(pid_t *child, int files[3],/* int pipefd[2], */char **cmds, char *env[]);
void	dup2_children(int max, int index, int pipefd[2], int files[3]);
# endif
void	wait_for_children(pid_t *children, int size);
char	**get_cmd_args(char *cmd);
int		check_cmd_env(char **cmd, char *env[]);

//ERRORS
int		error_manager(int erno);
char	*get_error_args(int erno);
char	*get_error_misc(int erno);
char	*add_prefix_sufix(char *error);


#endif