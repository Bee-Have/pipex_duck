/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 15:15:21 by user42            #+#    #+#             */
/*   Updated: 2022/02/08 16:38:25 by amarini-         ###   ########.fr       */
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

# define ERNO_NAME 1
# define ERNO_FILE 2
# define ERNO_PERMISSION 3
# define ERNO_NO_ARGS 4
# define ERNO_ARGS_NBR_LESS 5
# define ERNO_ARGS_NBR_MORE 6
# define ERNO_ARGS_NO_BONUS 7
# define ERNO_PATH 8

//MAIN
int		main(int ac, char **av, char *env[]);
char	**make_av_cmds(int ac, char **av);

//
//PARSING
int		parsing_manager(int ac, char **av);
int		parsing_args(int ac, char **av);
int		parsing_files(int ac, char **av);
//
//FORK
# ifndef BONUS

int		fork_manager(int files[2], char **cmds, char *env[]);
void	fork_cmds(pid_t *child, int files[2], char **cmds, char *env[]);

# else

int		fork_manager(int files[3], char ***cmds, char *env[]);
void	fork_cmds(pid_t *child, int files[3], char ***cmds, char *env[]);

# endif

char	**get_cmd_args(char *cmd);
int		check_cmd_env(char **cmd, char *env[]);
char	**get_possible_paths(char *env[]);
int		exit_bad_cmd(int erno, char **cmd, char **paths);

//
//FORK DUP
# ifndef BONUS

void	dupchild(int index, int pipefd[2], int files[2]);

# else

void	dupchild(int max, int index, int pipefd[2], int files[3]);
void	transit_pipe(int i, int pipefd[2], int pipehd[2], int files[3]);

# endif

void	tmp_pipe(int std);
void	dup_close_fd(int fd, int std);

//
//HERE_DOC
# ifdef BONUS

char	**get_lines_limiter(char *limiter);
void	write_here_doc_file(int stdin, char **here_doc);
void	here_doc_manager(char	***cmds, int (*pipehd)[2]);

# endif

//
//FORK UTILS
void	exit_child(pid_t *children, int ret);
int		wait_for_children(pid_t *children, int size);

//
//ERRORS
int		error_manager(int erno, char *str);
char	*get_error_args(int erno);
char	*get_error_misc(int erno, char *str, int *err);
char	*add_prefix_sufix(char *error);

#endif