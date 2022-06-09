/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_function.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 15:51:21 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/09 12:35:15 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	printf_args(t_node *head)
{
	t_node	*temporary;
	t_args	*tmp;
	int		i;

	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		tmp = (t_args *) temporary->content;
		printf("[arg %d : %s] -> ", i++, tmp->value);
		temporary = temporary->next;
	}
	printf("\n");
}

void	printf_redrection(t_node *head)
{
	t_node		*temporary;
	t_redirec	*tmp;
	int			i;

	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		tmp = (t_redirec *) temporary->content;
		printf("[redirction number %d type : %d, file: %s ]->",
			i++, tmp->e_rtype, tmp->file);
		temporary = temporary->next;
	}
	printf("\n");
}

void	printf_node(t_node *head)
{
	t_node	*temporary;
	t_cmd	*cmd;
	int		i;

	i = 0;
	temporary = head;
	while (temporary != NULL)
	{
		printf("cmd number :%d\n", i++);
		cmd = (t_cmd *)temporary->content;
		printf_args(cmd->args);
		printf("\n");
		printf_redrection(cmd->redrec);
		temporary = temporary->next;
	}
}
