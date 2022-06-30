/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_num.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchokri <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:58:41 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/25 18:58:46 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	str_to_num(const char *str)
{
	int				i;
	long			sign;
	unsigned long	res;

	i = 0;
	sign = 1;
	res = 0;
	while ((str[i] <= 13 && str[i] >= 9) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while ((str)[i])
	{
		if ((str)[i] <= '9' && (str)[i] >= '0')
		{
			res = res * 10 + (str)[i] - '0';
			i++;
		}
		else
		{
			printf("exit: %s: numeric argument required\n", str);
			break;	
			exit(EXIT_FAILURE);
		}
	}
	if (sign == 1 && res >= 9223372036854775807)
		return (-1);
	if (sign == -1 && res > 9223372036854775807)
		return (0);
	return (sign * res);
}
