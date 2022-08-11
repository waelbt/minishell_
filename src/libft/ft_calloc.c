/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 15:03:22 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:51:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_bzero(void *s, int n)
{
	char	*ptr;

	ptr = (char *) s;
	while (n-- > 0)
	{
		*(ptr++) = 0;
	}
}

void	*ft_calloc(int count, int size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
	{
		printf_error("minishell: ", "malloc: ",
			"failed cannot allocate memory\n");
		exit(1);
	}
	ft_bzero(ptr, count * size);
	return (ptr);
}
