/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:47:52 by lchokri           #+#    #+#             */
/*   Updated: 2022/07/21 13:33:52 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	my_exit(char *str)
{
	int		status;

	if (str == NULL)
		exit(0); //0 should be replaced by the global var because : WHEN EXIT HAVE NO PARAMETER, IT TAKES THE EXIT STATUS
				//OF THE LAST CMD EXECUTED
	else
	{
		status = str_to_num(str);
		status = (unsigned char)status; //// <-- hada howa lglobal var to be saved
		exit(255);
	}
}
