/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:51:39 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/26 17:07:21 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifdef BONUS

void	here_doc_manager(char	***cmds, int pipefd[2])
{
	char	*limiter;
	char	**tmp;
	char	**lines_limiter;

	limiter = ft_strdup((*cmds)[0]);
	tmp = ft_erase(*cmds, 1, 1);
	ft_freetab(*cmds);
	*cmds = tmp;
	ft_print_tab(*cmds);
	lines_limiter = get_lines_limiter(limiter);
	write_here_doc_file(pipefd[0], lines_limiter);
	free(limiter);
	// ft_freetab(lines_limiter);
}

char	**get_lines_limiter(char *limiter)
{
	char	*line;
	char	*prefix;
	char	**result;

	line = NULL;
	result = NULL;
	prefix = ft_strdup("pipe here_doc> ");
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
	ft_freetab(here_doc);
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
