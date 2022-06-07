/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 10:21:36 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 10:32:33 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_lstclear(t_node **lst, void (del)(void*))
{
	t_node	*tmp;

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
