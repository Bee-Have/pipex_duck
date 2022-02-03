/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 17:51:39 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/03 15:58:17 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

#ifdef BONUS

void	here_doc_manager(char	***cmds, int (*pipehd)[2])
{
	char	*limiter;
	char	**tmp;
	char	**lines_limiter;

	limiter = ft_strdup((*cmds)[0]);
	tmp = ft_erase(*cmds, 0, 1);
	ft_freetab(*cmds);
	*cmds = tmp;
	pipe(*pipehd);
	lines_limiter = get_lines_limiter(limiter,
			ft_tablen((const char **)*cmds));
	write_here_doc_file((*pipehd)[1], lines_limiter);
	close((*pipehd)[1]);
	free(limiter);
	ft_freetab(lines_limiter);
}

char	**get_lines_limiter(char *limiter, int cmd_len)
{
	char	*line;
	char	*prefix;
	char	**result;

	line = NULL;
	result = NULL;
	prefix = make_here_doc_prefix(cmd_len - 1);
	while (ft_strcmp(line, limiter) == 1)
	{
		free(line);
		write(STDOUT_FILENO, prefix, ft_strlen(prefix));
		get_next_line(STDIN_FILENO, &line);
		result = ft_add_tab(result, line);
	}
	get_next_line(-42, NULL);
	free(line);
	free(prefix);
	return (result);
}

char	*make_here_doc_prefix(int cmd_len)
{
	int		i;
	char	*tmp;
	char	*prefix;

	i = 0;
	tmp = NULL;
	prefix = ft_strdup("here_doc> ");
	while (i < cmd_len)
	{
		free(tmp);
		tmp = ft_strjoin("pipe ", prefix);
		free(prefix);
		prefix = ft_strdup(tmp);
		++i;
	}
	free(tmp);
	return (prefix);
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

int	wait_for_children(pid_t *children, int size)
{
	int	i;
	int	ret_child;
	char	*tmp;

	i = 0;
	while (i < size)
	{
		ret_child = 0;
		waitpid(children[i], &ret_child, WUNTRACED);
		tmp = ft_itoa(ret_child);
		write(2, tmp, ft_strlen(tmp));
		write(2, "\n", 1);
		++i;
	}
	free(children);
	return (ret_child);
}
