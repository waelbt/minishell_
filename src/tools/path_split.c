/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:59:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/08 18:01:48 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count(char *s, char c)
{
	int stock;
	int i;

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

static int	ft_no_25line(char *s, char c,	char **str, int start)
{
	int		t;
	int		j;
	int		i;

	i = 0;
	t = 0;
	j = 0;
	while (i <= ft_strlen(s))
	{
		if (s[i] == c && i == 0)
		{
			str[j++] = ft_strdup("");
		}
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
			while(i != ft_strlen(s) && (s[i + 1] == c || s[i + 1] == '\0') )
			{
				str[j++] = ft_strdup("");
				if (!str[j - 1])
					return (free_handle(j - 1, str));
				i++;
			}
			t = 0;
		}
		i++;
	}
	str[j] = NULL;
	return (1);
}

char	**split_path(char *s, char c)
{
	int		i;
	char	**str;

	if (s == NULL)
		return NULL;
	str = (char **) malloc((ft_count(s, c) + 1) * sizeof(char *));
	if (!str)
		return (0);
	i = ft_no_25line(s, c, str, 0);
	if (i == 0)
		return (NULL);
	return (str);
}
