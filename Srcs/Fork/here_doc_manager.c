/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/04 18:42:25 by amarini-          #+#    #+#             */
/*   Updated: 2022/02/04 19:05:23 by amarini-         ###   ########.fr       */
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
	lines_limiter = get_lines_limiter(limiter);
	write_here_doc_file((*pipehd)[1], lines_limiter);
	close((*pipehd)[1]);
	free(limiter);
	ft_freetab(lines_limiter);
}

char	**get_lines_limiter(char *limiter)
{
	char	*line;
	char	*prefix;
	char	**result;

	line = NULL;
	result = NULL;
	prefix = ft_strdup("> ");
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
