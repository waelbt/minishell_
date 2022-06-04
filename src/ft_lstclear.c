/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 20:24:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_lstclear(t_token **lst, void (del)(void*))
{
	t_token	*tmp;

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
