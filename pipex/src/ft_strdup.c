/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:55:04 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/19 15:31:43 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		j;
	char	*ptr;

	i = ft_strlen((char *)s1);
	j = 0;
	ptr = (char *) malloc((i + 1) * sizeof(char));
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
