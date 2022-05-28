/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:07:27 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/28 15:00:44 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*ft_strchr(char *s, int c)
{
	size_t		i;
	char		*p;

	i = 0;
	p = (char *) s;
	while (i <= ft_strlen(s))
	{
		if (*(p + i) == (char )c)
			return (p + i);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int main(void)
{
	char s[] = "tripouille";
	printf("%s \n",ft_strchr(s, 't' + 256));
	printf("%s",strchr(s, 't' + 256));
}
*/