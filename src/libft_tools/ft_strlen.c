/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:32:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/10 15:22:07 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_type(char *c)
{
	if (!ft_strcmp(c, "<"))
		return (0);
	else if (!ft_strcmp(c, ">"))
		return (1);
	else if (!ft_strcmp(c, "<<"))
		return (2);
	else if (!ft_strcmp(c, ">>"))
		return (3);
	return (-1);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
