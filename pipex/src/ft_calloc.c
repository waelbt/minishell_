/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 14:15:31 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/19 15:22:40 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"


void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
	{
		*(char *)s = '\0';
		s++;
		n--;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}
