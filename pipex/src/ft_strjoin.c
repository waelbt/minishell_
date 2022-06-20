/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 15:18:17 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/19 16:00:59 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	int		j;

	j = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (NULL);
	while (i < ft_strlen(s1) + ft_strlen(s2))
	{
		while (s1[i])
		{
			str[i] = s1[i];
			i++;
		}
		while (s2[j])
			str[i++] = s2[j++];
	}
	str[i] = '\0';
	free(s1);
	free(s2);
	return (str);
}
