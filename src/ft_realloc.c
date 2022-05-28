/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:52:55 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/27 21:24:53 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void *ft_realloc(void *ptr, size_t size)
{
	int				i;
	unsigned char	*p;
	unsigned char	*s;

	i = 0;
	p = (unsigned char *) ptr;
	s = calloc(size, sizeof(void));
	while(p[i])
	{
		s[i] = p[i];
		i++;
	}
	while(i < size)
		s[i++] = '\0';
	free(ptr);
	return ((void *) s);
}
