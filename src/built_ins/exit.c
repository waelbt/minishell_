/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:47:52 by lchokri           #+#    #+#             */
/*   Updated: 2022/08/02 11:46:22 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	is_num(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	my_exit(char **str)
{
	int		len;

	len = double_pointer_len(str);
	printf_error("exit\n", NULL, NULL);
	if (len >= 2 && !is_num(str[1]))
	{
		printf_error("minishell: exit: ",
			str[1], ": numeric argument required\n");
		exit(255);
	}
	else if (len <= 2)
	{
		if (str[1])
			ft_setter(ft_atoi(str[1]));
		exit(ft_getter());
	}
	else
	{
		ft_setter(1);
		printf_error("minishell: exit: too many arguments\n", NULL, NULL);
	}
}
