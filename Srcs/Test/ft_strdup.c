/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarini- <amarini-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 07:41:27 by amarini-          #+#    #+#             */
/*   Updated: 2022/01/21 14:41:21 by amarini-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int	ft_strlen(const char *s);

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*cp;

	i = 0;
	cp = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cp)
		return (NULL);
	cp[ft_strlen(s1)] = '\0';
	while (s1[i] != '\0')
	{
		cp[i] = s1[i];
		i++;
	}
	return (cp);
}
