/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 09:30:26 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 20:46:52 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_node	*ft_lstnew(void *content)
{
	t_node	*new;

	if (!content)
		return (NULL);
	new = ft_calloc(1, sizeof(t_node));
	new->content = content;
	new->next = NULL;
	return (new);
}
