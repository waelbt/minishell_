/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 12:48:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/28 19:02:37 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	skipper(char *str, int *i, int c)
{
	(*i)++;
	while(str[*i] != c)
		(*i)++;
	(*i)++;
}

int	ft_counter(char *str)
{
	int i;
	int	counter;

	counter = 0;
	i = 0;
	while (str[0] == 32)
		i++;
	while (str[i])
	{
		if(str[i] == '\'')
		{
			skipper(str, &i, '\'');
			continue;
		}
		if(str[i] == '"')
		{
			skipper(str, &i, '"');
			continue;
		}
		if(str[i] == 32 && str[i + 1] != 32 
				&& str[i + 1] != '\0')
			counter++;
		i++;
	}
	return (counter);
}

char	**advanced_split(char *str)
{
	char	**value;
	int		i;
	int		index;
	int		start;
	int		stopper;

	i = 0;
	stopper = 0;
	index	= 0;
	start = 0;
	value = (char **) malloc((ft_counter(str) + 1) * sizeof(char *));
	if (!value)
		return NULL;
	while (i <= ft_strlen(str))
	{
		if (str[i] !=  32 && stopper == 0)
		{
			start = i;
			stopper = 1;
		}
		if(str[i] == '\'')
		{
			skipper(str, &i, '\'');
			continue;
		}
		if(str[i] == '"')
		{
			skipper(str, &i, '"');
				continue;
		}
		if ((str[i] == 32 || i == ft_strlen(str)) && stopper == 1)
		{
			value[index] = ft_substr(str, start, (i - start));
			printf("%p\n",value[index]);
			index++;
			stopper = 0;
		}
		i++;
	}
	/*leaks deyal fail*/
	value[index] = NULL;
	printf("%p\n",value);
	//free(str);
	return (value);
}