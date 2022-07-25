/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:02:54 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/24 04:09:50 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_double_char(char **tmp, int t)
{
	int	i;

	i = 0;
	if (!tmp)
		return ;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	if (t == 0)
		free(tmp);
}

void	lexer_previous(t_lexer	*lexer)
{
	if (lexer->i != 0)
	{
		lexer->i -= 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

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
		free_double_char(tmp->after_expand, 0);
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
		free_double_char(tmp->after_expand, 0);
		free(tmp->path);
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
		cmd = (t_cmd *)temporary->content;
		s = temporary;
		dda(&cmd->args);
		fed(&cmd->redrec);
		free_double_char(cmd->after_expand, 0);
		free(cmd);
		temporary = temporary->next;
		free(s);
	}
}
