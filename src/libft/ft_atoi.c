/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 15:13:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/22 11:27:16 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	max_min_value(int stock, int signe, int i)
{
	if (i >= 19 && signe < 0)
		return (stock = 0);
	if (i >= 19 && signe > 0)
		return (stock = -1);
	else
		return (stock);
}

int	ft_atoi(const char *ptr)
{
	int	signe;
	int	i;
	int	stock;

	i = 0;
	signe = 1;
	stock = 0;
	while (ptr[i] == ' ' || ptr[i] == '\n' || ptr[i] == '\t'
		|| ptr[i] == '\v' || ptr[i] == '\r' || ptr[i] == '\f')
		i++;
	if (ptr[i] == '+' || ptr[i] == '-')
	{
		if (ptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (ptr[i] >= '0' && ptr[i] <= '9')
	{
		stock = (stock * 10) + (ptr[i] - '0');
		i++;
	}
	stock = max_min_value(stock, signe, i);
	return (stock * signe);
}
