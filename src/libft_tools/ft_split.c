/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 11:31:23 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/12 17:42:07 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count(char const *s, char c)
{
	int	stock;

	stock = 0;
	while (*s == c)
		s++;
	while (*s)
	{
		if (*s == c && (*(s + 1) != c && *(s + 1) != '\0'))
			stock++;
		s++;
	}
	return (stock + 1);
}

static int	free_handle(int j, char **str)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (0);
}

static int	ft_no_25line(char *s, char c,	char **str, int start)
{
	int		t;
	int		j;
	size_t	i;

	i = 0;
	t = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] != c && t == 0)
		{
			start = i;
			t = 1;
		}
		else if ((s[i] == c || i == ft_strlen(s)) && t == 1)
		{
			str[j++] = ft_substr(s, start, (i - start));
			if (!str[j - 1])
				return (free_handle(j - 1, str));
			t = 0;
		}
		i++;
	}
	str[j] = NULL;
	return (1);
}

char	**ft_split(char *s, char c)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (0);
	str = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	i = ft_no_25line(s, c, str, 0);
	if (i == 0)
		return (NULL);
	return (str);
}
