/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 18:04:04 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/30 08:55:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		len;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
	{
		return (0);
	}
	while (i < len)
	{
		if (i < ft_strlen(s1))
			*(ptr + i) = *(s1 + i);
		else if (i >= ft_strlen(s1))
			*(ptr + i) = *(s2++);
		i++;
	}
	*(ptr + i) = '\0';
	return (ptr);
}
