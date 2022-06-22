/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:02:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/21 17:40:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	dda(t_node **head)
{
	t_node	*temporary;
	t_args	*tmp;
	t_node	*s;
	int		i;

	i = 0;
	temporary = *head;
	while (temporary != NULL)
	{
		tmp = (t_args *) temporary->content;
		s = temporary;
		free(tmp->value);
		free(tmp);
		temporary = temporary->next;
		free(s);
	}
}

void	fed(t_node **head)
{
	t_node		*temporary;
	t_redirec	*tmp;
	t_node		*s;
	int			i;

	temporary = *head;
	i = 0;
	while (temporary != NULL)
	{
		tmp = (t_redirec *)temporary->content;
		s = temporary;
		free(tmp->file);
		free(tmp);
		temporary = temporary->next;
		free(s);
	}
}

void	free_node(t_node **head)
{
	t_node	*temporary;
	t_cmd	*cmd;
	int		i;
	t_node	*s;

	temporary = *head;
	i = 0;
	while (temporary != NULL)
	{
		//printf("cmd number :%d\n", i++);
		cmd = (t_cmd *)temporary->content;
		s = temporary;
		dda(&cmd->args);
		fed(&cmd->redrec);
		free_double_char(cmd->after_expand);
		free(cmd);
		temporary = temporary->next;
		free(s);
		//system("leaks minishell");
	}
}
