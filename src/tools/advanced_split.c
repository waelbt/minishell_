/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:48:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:50:17 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	skipper(char *str, int *i, int c)
{
	(*i)++;
	while (str[*i] != c)
		(*i)++;
	(*i)++;
}

int	ft_counter(char *str)
{
	int	i;
	int	counter;

	counter = 1;
	i = 0;
	while (str[i] == 32)
		i++;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			skipper(str, &i, str[i]);
			continue ;
		}
		if (str[i] == 32 && str[i + 1] != 32
			&& str[i + 1] != '\0')
			counter++;
		i++;
	}
	return (counter);
}

char	**free_handle_d(int j, char **str)
{
	while (j >= 0)
	{
		free(str[j]);
		j--;
	}
	free(str);
	return (NULL);
}

int	norm_33(char *str, int *i)
{
	if (str[i[0]] != 32 && str[i[0]] && i[3] == 0)
	{
		i[2] = i[0];
		i[3] = 1;
	}
	if (str[i[0]] == '"' || str[i[0]] == '\'')
	{
		skipper(str, &i[0], str[i[0]]);
		return (1);
	}
	return (0);
}

char	**advanced_split(char *str)
{
	char	**value;
	int		i[4];

	init_array(i, 4);
	value = (char **) ft_calloc(ft_counter(str) + 1, sizeof(char *));
	if (!value)
		return (NULL);
	while (i[0] <= ft_strlen(str))
	{
		if (norm_33(str, i))
			continue ;
		if ((str[i[0]] == 32 || i[0] == ft_strlen(str)) && i[3] == 1)
		{
			value[i[1]++] = ft_substr(str, i[2], (i[0] - i[2]));
			if (!value[i[1] - 1])
				return (free_handle_d(i[1] - 1, value));
			i[3] = 0;
		}
		i[0]++;
	}
	value[i[1]] = NULL;
	return (value);
}
