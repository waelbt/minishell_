/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:03:30 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:47:23 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*ptr;

	i = ft_strlen((char *)s1);
	j = 0;
	ptr = (char *) ft_calloc(i + 1, sizeof(char));
	if (!ptr)
		return (0);
	while (j < i)
	{
		*(ptr + j) = *(s1 + j);
		j++;
	}
	*(ptr + j) = '\0';
	return (ptr);
}
