/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:49:04 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 10:32:26 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_lstadd_front(t_node **list, t_node *new)
{
	new->next = *list;
	*list = new;
}

/*
#include <stdio.h>
void printflinklist(cmd_T *head)
{
	t_list *temporary = head;
    while(temporary != NULL)
    {
        printf("%s - ",(char *)temporary->content);
        temporary = temporary->next;
    }
    printf("\n");
}
int main(void)
{
	t_list *list = NULL;
	t_list *tmp;
	
	tmp = ft_lstnew("dadadd");
	tmp->next = list;
	list = tmp;
	tmp = ft_lstnew("wael");
	tmp->next = list;
	list = tmp;
	tmp = ft_lstnew("walid");
	tmp->next = list;
	list = tmp;
	ft_lstadd_front(&list, ft_lstnew("test"));
	printflinklist(list);	
}
*/