/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:54:00 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:46:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_array(int *i, int size)
{
	int	co;

	co = -1;
	while (++co < size)
		i[co] = 0;
}

static int	intlen(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*negative_n(int n, char *str)
{
	int				i;
	int				s;
	unsigned int	w;

	w = (unsigned int) n * (-1);
	s = intlen(n) + 1;
	i = s;
	str = (char *) ft_calloc(s + 1, sizeof(char));
	if (!str)
		return (0);
	while (s > 1)
	{
		str[s - 1] = (w % 10) + '0';
		w = w / 10;
		s--;
	}
	str[0] = '-';
	str[i] = '\0';
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	int		s;
	char	*str;

	str = NULL;
	if (n < 0)
	{
		str = negative_n(n, str);
	}
	else
	{
		s = intlen(n);
		i = s;
		str = (char *) ft_calloc(s + 1, sizeof(char));
		if (!str)
			return (0);
		while (s > 0)
		{
			str[s - 1] = (n % 10) + '0';
			n = n / 10;
			s--;
		}
		str[i] = '\0';
	}
	return (str);
}
