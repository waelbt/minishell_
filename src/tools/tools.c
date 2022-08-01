/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 14:23:31 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 14:23:45 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	set_to_defaults(char *str)
{
	int j = 0;
	while(str[j])
	{
		if(str[j] == -1)
			str[j] = '\'';
		if(str[j] == -2)
			str[j] = '"';
		j++;
	}
}

void 	quotes_replace(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'')
			str[i] = -1;
		if(str[i] == '"')
			str[i] = -2;
		i++;
	}
}