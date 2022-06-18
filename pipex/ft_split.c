/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 04:18:46 by lchokri           #+#    #+#             */
/*   Updated: 2021/11/26 03:18:04 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	wordcount(const char *s, char c)
{
	int	j;
	int	i;
	int	check;

	i = 0;
	j = 0;
	while (s[i])
	{
		check = 0;
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			check = 1;
			i++;
		}
		if (check == 1)
			j++;
	}
	return (j);
}

static int	wordlen(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s != c && *s != '\0')
	{
		i++;
		s++;
	}
	return (i);
}

static void	freeptr(char **p)
{
	int	i;

	i = 0;
	while (p[i])
	{
		free(p[i]);
		i++;
	}
	free(p);
}

static char	**retptr(const char *s, char c, int *j, char **p)
{
	int	k;
	int	len;

	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (!*s)
			break ;
		len = wordlen(s, c);
		p[++*j] = (char *)ft_calloc((len + 1), sizeof(char));
		if (!p[*j])
		{
			freeptr(p);
			return (NULL);
		}
		k = 0;
		while (k < len)
		{
			p[*j][k++] = *s++;
		}
	}
	return (p);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	int		i;
	char	**p;

	i = 0;
	if (!s)
		return (NULL);
	i = wordcount(s, c);
	p = (char **)ft_calloc((i + 1), sizeof(char *));
	if (!p)
		return (NULL);
	j = -1;
	p = retptr(s, c, &j, p);
	return (p);
}
