/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:57:02 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 14:29:32 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_check(char *str)
{
	int	i;

	if (ft_strncmp(str, "-n", 2))
		return (0);
	i = 2;
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_flag(char **after_expand, int *check)
{
	int	i;

	i = 1;
	while (after_expand[i])
	{
		if (!ft_check(after_expand[i]))
			return (i);
		*check = 1;
		i++;
	}
	return (-1);
}

void	echo(char **after_expand)
{
	int		i;
	int		check;
	char	*str;

	i = 1;
	check = 0;
	str = NULL;
	ft_setter(0);
	if (!after_expand[1])
		printf("\n");
	else
	{
		i = check_flag(after_expand, &check);
		if (i == -1)
			return ;
		write(1, after_expand[i], ft_strlen(after_expand[i]));
		while (after_expand[++i])
		{
			write(1, " ", 1);
			write(1, after_expand[i], ft_strlen(after_expand[i]));
		}
		if (check == 0)
			printf("\n");
	}
}
