/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:55:04 by lchokri           #+#    #+#             */
/*   Updated: 2021/11/24 00:32:17 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*p;

	i = 1;
	if (s1[i] != '\0')
	{
		while (s1[i])
			i++;
		p = malloc(sizeof(char) * i + 1);
		if (p == NULL)
			return (NULL);
		i = 0;
		while (s1[i] != '\0')
		{
			p[i] = s1[i];
			i++;
		}
		p[i] = '\0';
	}
	else
	{
		p = malloc(sizeof(char));
		p[i] = '\0';
	}
	return ((char *)p);
}
