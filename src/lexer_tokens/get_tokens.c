/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:41:25 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/05 19:40:15 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_redirec	*init_redirection(t_token **token, t_lexer *lexer)
{
	t_redirec	*redrec;

	redrec = ft_calloc(1, sizeof(t_redirec));
	if (!redrec)
		return (NULL);
	redrec->e_rtype = get_type((*token)->value);
	redrec->after_expand = NULL;
	free((*token)->value);
	free((*token));
	*token = lexer_get_next_token(lexer);
	if ((*token)->e_type == TOKEN_STRING)
		redrec->file = ft_strdup((*token)->value);
	else
	{
		if(!ft_strcmp((*token)->value, ""))
		{
			free((*token)->value);
			(*token)->value = ft_strdup("newline");
		}
		ft_setter(258);
		printf_error("minishell: syntax error near unexpected token `", (*token)->value, "'\n");
		redrec->e_rtype = ERROR;
	}
	return (redrec);
}

void	*init_cmd1(t_token **token, t_node **tmp, t_cmd **cmd)
{
	t_args	*arg;

	if ((*token)->e_type == TOKEN_STRING)
	{
		arg = ft_calloc(1, sizeof(t_args));
		if (!arg)
			return (NULL);
		arg->value = ft_strdup((*token)->value);
		arg->after_expand = NULL;
		(*cmd)->args = ft_lstnew((void *)arg);
		ft_lstadd_back(tmp, (*cmd)->args);
	}
	return ((void *)1);
}

void	*init_cmd2(t_token **token, t_node **tmp1, t_cmd **cmd, t_lexer *lexer)
{
	if ((*token)->e_type == TOKEN_REDICRECTION)
	{
		(*cmd)->redrec = ft_lstnew((void *)init_redirection(token, lexer));
		if (((t_redirec *)(*cmd)->redrec->content)->e_rtype == ERROR)
		{
			free_redirc(&(*cmd)->redrec);
			return (NULL);
		}
		ft_lstadd_back(tmp1, (*cmd)->redrec);
	}
	return ((void *)1);
}

void	*clear_error(t_cmd *cmd, t_node *tmp, t_node *tmp1)
{
	free_args(&tmp);
	free_redirc(&tmp1);
	free(cmd);
	return (NULL);
}

t_cmd	*init_cmd(t_lexer *lexer, t_token **token)
{
	t_cmd	*cmd;
	t_node	*tmp;
	t_node	*tmp1;

	tmp = NULL;
	tmp1 = NULL;
	
	cmd = ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->after_expand = NULL;
	cmd->output = NULL;
	cmd->input = NULL;
	while ((*token) && (*token)->e_type != TOKEN_EOF
		&& (*token)->e_type != TOKEN_PIPE)
	{
		if ((*token)->e_type == TOKEN_ERROR)
			return (clear_error(cmd, tmp, tmp1));
		if (!init_cmd1(token, &tmp, &cmd)
			|| !init_cmd2(token, &tmp1, &cmd, lexer))
			return (clear_error(cmd, tmp, tmp1));
		free((*token)->value);
		free(*token);
		(*token) = lexer_get_next_token(lexer);
	}
	cmd->args = tmp;
	cmd->redrec = tmp1;
	return (cmd);
}
