/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:59:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 03:42:37 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count(char *s, char c)
{
	int	stock;
	int	i;

	stock = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			stock++;
		i++;
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

int	norm_advance(char *s, char c, char **str, int *i)
{
	while (i[0] != ft_strlen(s) && (s[i[0] + 1] == c || s[i[0] + 1] == '\0'))
	{
		str[i[1]++] = ft_strdup("");
		if (!str[i[1] - 1])
			return (1);
		i[0]++;
	}
	return (0);
}

static int	ft_no_25line(char *s, char c,	char **str, int start)
{
	int		i[3];

	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	while (i[0] <= ft_strlen(s))
	{
		if (s[i[0]] == c && i[0] == 0)
			str[i[1]++] = ft_strdup("");
		if (s[i[0]] != c && i[2] == 0)
		{
			start = i[0];
			i[2] = 1;
		}
		else if ((s[i[0]] == c || i[0] == ft_strlen(s)) && i[2] == 1)
		{
			str[i[1]++] = ft_substr(s, start, (i[0] - start));
			if (!str[i[1] - 1] || norm_advance(s, c, str, i))
				return (free_handle(i[1] - 1, str));
			i[2] = 0;
		}
		i[0]++;
	}
	str[i[1]] = NULL;
	return (1);
}

char	**split_path(char *s, char c)
{
	int		i;
	char	**str;

	if (s == NULL)
		return (NULL);
	str = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	i = ft_no_25line(s, c, str, 0);
	if (i == 0)
		return (NULL);
	return (str);
}
