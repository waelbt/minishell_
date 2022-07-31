/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 16:52:55 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/30 08:54:01 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_realloc(char *ptr, int size)
{
	int				i;
	char			*s;

	i = 0;
	s = ft_calloc(size, sizeof(unsigned char));
	while (ptr[i])
	{
		s[i] = ptr[i];
		i++;
	}
	while (i < size)
		s[i++] = '\0';
	return (s);
}
