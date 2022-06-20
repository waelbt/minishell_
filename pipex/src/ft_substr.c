/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 17:33:49 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/19 17:00:30 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	j;
	char	*ptr;

	j = 0;
	if (!s)
		return (0);
	if (ft_strlen((char *)s) - start < len)
		len = ft_strlen((char *)s) - start;
	else if (start > ft_strlen((char *)s) + 1)
	{
		ptr = (char *) malloc(1);
		*ptr = 0;
		return (ptr);
	}
	ptr = (char *) malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (0);
	while (j < len)
	{
		*(ptr + j) = *(s + start + j);
		j++;
	}
	*(ptr + j) = '\0';
	return (ptr);
}
