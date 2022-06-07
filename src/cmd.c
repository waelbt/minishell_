/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:41:25 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 16:58:46 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int get_type(char *c)
{
	if(!ft_strcmp(c , "<"))
		return (0);
	else if(!ft_strcmp(c , ">"))
		return (1);
	else if(!ft_strcmp(c , "<<"))
		return (2);
	else if(!ft_strcmp(c , ">>"))
		return (3);
	return (-1);
}

t_args  *init_arg(char *str)
{
	t_args *arg;

	arg = malloc(sizeof(t_args));
	if(!arg)
		return (NULL);
	arg->value = str;
	/*in case we need to add some elements 
	in our data structer in the future */
	return (arg);
}

t_redirec  *init_redirection(char *str, t_lexer *lexer)
{
	t_redirec	*redrec;
	t_token		*token;

	redrec = malloc(sizeof(t_redirec));
	if (!redrec)
		return (NULL);
	redrec->e_rtype = get_type(str);
	token = lexer_get_next_token(lexer);
	if(token->e_type == TOKEN_STRING)
	{
		redrec->file = token->value;
		// red->fd = open(red->file, O_RDWR | O_CREAT); //3la 7ssab type wach 4adi t ready ou la t creat
	}
	else
	{
		printf("parse error 'missing redirection file'\n");
		redrec->e_rtype = ERROR;
	}
	return (redrec);
}

t_cmd	*init_cmd(t_lexer *lexer, t_token *token)
{
	t_cmd	*cmd;
	t_node	*tmp;
	t_node	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	while (token && token->e_type != TOKEN_EOF && token->e_type != TOKEN_PIPE)
	{
		if(token->e_type == TOKEN_ERROR)
			return (NULL);
		if (token->e_type == TOKEN_STRING)
		{
			cmd->args = ft_lstnew((void *) init_arg(token->value));
			ft_lstadd_back(&tmp ,cmd->args);
		}
		else if (token->e_type == TOKEN_REDICRECTION)
		{
			cmd->redrec = ft_lstnew((void *) init_redirection(token->value, lexer));
			if(((t_redirec *)cmd->redrec->content)->e_rtype == ERROR)
				return (NULL);
			ft_lstadd_back(&tmp1 ,cmd->redrec);
		}
		token = lexer_get_next_token(lexer);
	}
	cmd->args = tmp;
	cmd->redrec = tmp1;
	return (cmd);
}