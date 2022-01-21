/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 07:42:58 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/21 14:37:42 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	calc_row(char const *s, char sep)
{
	int		i;
	int		row;

	i = 0;
	row = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == sep)
			i++;
		if (s[i] != '\0' && s[i] != sep)
			row++;
		while (s[i] != '\0' && s[i] != sep)
			i++;
	}
	return (row);
}

int	calc_word(char const *s, char sep, int strpos)
{
	int		length;

	length = 0;
	while (s[strpos] != '\0')
	{
		if (s[strpos] == sep)
		{
			if (length == 0)
				return (1);
			return (length);
		}
		strpos++;
		length++;
	}
	if (length == 0)
		return (1);
	return (length);
}

char	*fill_array(char *result, char const *s, int i, char sep)
{
	int		icol;

	icol = 0;
	while (s[i] != '\0' && s[i] != sep)
	{
		result[icol] = s[i];
		icol++;
		i++;
	}
	return (result);
}

char	**free_everything(char **result)
{
	int		irow;

	irow = 0;
	while (result[irow] != NULL)
	{
		free(result[irow]);
		irow++;
	}
	free(result);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		irow;
	char	**result;

	if (!s)
		return (NULL);
	irow = 0;
	i = 0;
	result = (char **)malloc((calc_row(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	result[calc_row(s, c)] = NULL;
	while (irow < calc_row(s, c))
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		result[irow] = (char *)malloc((calc_word(s, c, i) + 1) * sizeof(char));
		if (!result[irow])
			return (free_everything(result));
		result[irow][calc_word(s, c, i)] = '\0';
		result[irow] = fill_array(result[irow], s, i, c);
		i += calc_word(s, c, i);
		irow++;
	}
	return (result);
}
