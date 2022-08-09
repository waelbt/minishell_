/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 09:53:08 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/21 18:05:14 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isalpha(int c)
{
	unsigned int	b;

	if (c >= 65 && c <= 90)
		return (b = 1);
	else if (c >= 97 && c <= 122)
		return (b = 2);
	else
		return (b = 0);
}
