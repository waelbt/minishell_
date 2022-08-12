/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 11:42:47 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 01:23:53 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	printf_error(char *p, char *str, char *s)
{
	if (p)
		write(2, p, ft_strlen(p));
	if (str)
		write(2, str, ft_strlen(str));
	if (s)
		write(2, s, ft_strlen(s));
}

static int	*exit_code(void)
{
	static int	c;

	return (&c);
}

int	ft_getter(void)
{
	int	*i;

	i = exit_code();
	return (*i);
}

void	ft_setter(int value)
{
	int	*i;

	i = exit_code();
	*i = value;
}
