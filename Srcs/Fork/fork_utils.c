/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:51:39 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/27 17:38:18 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifdef BONUS

void	here_doc_manager(char	***cmds, int pipefd[2], int files[3])
{
	char	*limiter;
	char	**tmp;
	char	**lines_limiter;

	// printf("in here_doc manager\n");
	limiter = ft_strdup((*cmds)[0]);
	tmp = ft_erase(*cmds, 1, 1);
	ft_freetab(*cmds);
	*cmds = tmp;
	// ft_print_tab(*cmds);
	lines_limiter = get_lines_limiter(limiter,
					ft_tablen((const char **)*cmds));
	write_here_doc_file(pipefd[1], lines_limiter);
	free(limiter);
	ft_freetab(lines_limiter);
	(void)files;
	// dup2(pipefd[0], files[2]);
	// transit_pipe(0, pipefd, files);
}

char	**get_lines_limiter(char *limiter, int cmd_len)
{
	char	*line;
	char	*prefix;
	char	**result;
	int		i;

	line = NULL;
	result = NULL;
	i = 0;
	prefix = ft_strdup("here_doc> ");
	while (i < cmd_len - 1)
	{
		free(line);
		line = ft_strjoin("pipe ", prefix);
		free(prefix);
		prefix = ft_strdup(line);
		++i;
	}
	while (ft_strcmp(line, limiter) == 1)
	{
		free(line);
		write(STDOUT_FILENO, prefix, ft_strlen(prefix));
		get_next_line(STDIN_FILENO, &line);
		result = ft_add_tab(result, line);
	}
	free(line);
	free(prefix);
	return (result);
}

void	write_here_doc_file(int fd, char **here_doc)
{
	int	i;

	i = 0;
	while (here_doc[i])
	{
		write(fd, here_doc[i], ft_strlen(here_doc[i]));
		write(fd, "\n", 1);
		++i;
	}
}

#endif

void	wait_for_children(pid_t *children, int size)
{
	int	i;
	int	ret_child;

	i = 0;
	ret_child = 0;
	while (i < size)
	{
		waitpid(children[i], &ret_child, WUNTRACED);
		++i;
	}
}
