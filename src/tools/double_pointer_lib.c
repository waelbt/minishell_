/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_pointer_lib.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:09:15 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 14:16:56 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**join_double_pointer(char **str, char **ptr)
{
	char	**join;
	int		len[3];
	int		index;
	int		j;

	if (!ptr)
		return (str);
	index = 0;
	j = 0;
	len[0] = double_pointer_len(str);
	len[1] = double_pointer_len(ptr);
	len[2] = len[0] + len[1];
	join = (char **) ft_calloc((len[2] + 1) ,sizeof(char *));
	if (!join)
		return (NULL);
	while (index < len[2])
	{
		if (index < len[0])
			join[index] = str[index];
		else if (index >= len[0])
			join[index] = ptr[j++];
		index++;
	}
	join[index] = NULL;
	free(str);
	free(ptr);
	return (join);
}

char 	**ft_strdup_double(char **ptr)
{
	char	**str;
	int		i;
	int		len;

	len = double_pointer_len(ptr);
	str = (char **)malloc((len + 1) * sizeof(char *));
	if(!str)
		return (NULL);
	i = 0;
	while(i < len)
	{
		str[i] = ft_strdup(ptr[i]);
		i++;
	}
	str[i] = NULL;
	return (str);
}
