/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:02:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/28 19:02:44 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	dda(t_node **head)
{
	t_node	*temporary;
	t_args	*tmp;
	t_node	*s;
	int		i;

	temporary = *head;
	while (temporary != NULL)
	{
		tmp = (t_args *) temporary->content;
		s = temporary;
		printf("%p\n",tmp->after_expand[0]);
		printf("%p\n",tmp->after_expand[1]);
		printf("%p\n",tmp->after_expand);
		free_double_char(tmp->after_expand);
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
		free(cmd);
		temporary = temporary->next;
		free(s);
		//system("leaks minishell");
	}
}
