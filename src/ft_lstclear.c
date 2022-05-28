/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/27 15:17:42 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_lstclear(token_T **lst, void (del)(void*))
{
	token_T	*tmp;

	if (!*lst)
		return ;
	tmp = *lst;
	while (*lst)
	{
		tmp = tmp->next;
		// ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}
