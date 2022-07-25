/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:47:52 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/22 23:23:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int		is_num(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

void	my_exit(char **str)
{
	int		status;
	int		len;

	len = double_pointer_len(str);
	if(len >= 2 && !is_num(str[1]))
	{
		printf_error("exit\n", NULL, NULL);
		printf_error("minishell: exit: ", (char *)str[1], ": numeric argument required\n");
		exit(255);
	}
	else if(len <= 2)
	{
		printf("exit\n");
		if (str[1] == NULL)
			exit(ft_getter());
		else
		{
			status = ft_atoi(str[1]);
			exit(status);
		}
	}
	else
	{
		ft_setter(1);
		printf_error("exit\n", NULL, NULL);
		printf_error("minishell: exit: too many arguments\n", NULL, NULL);
	}
}
