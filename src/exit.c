/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:47:52 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/21 18:58:17 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	my_exit(char **str)
{
	int		status;
	int		len;

	len = double_pointer_len(str);
	if(len <= 2)
	{
		if (str[1] == NULL)
			exit(ft_getter());
		else
		{
			status = str_to_num(str[1]);
			ft_setter(status);
			exit(ft_getter);
		}
	}
	else
	{
		printf_error("exit\n", NULL, NULL);
		printf_error("minishell: exit: too many arguments\n", NULL, NULL);
	}
}
