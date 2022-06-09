/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 12:41:25 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/09 09:45:07 by waboutzo         ###   ########.fr       */
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

	arg = ft_calloc(1, sizeof(t_args));
	if(!arg)
		return (NULL);
	arg->value = str;
	/*in case we need to add some elements 
	in our data structer in the future */
	return (arg);
}

t_redirec  *init_redirection(t_token **token, t_lexer *lexer)
{
	t_redirec	*redrec;

	redrec = ft_calloc(1, sizeof(t_redirec));
	if (!redrec)
		return (NULL);
	redrec->e_rtype = get_type((*token)->value);
	free((*token)->value);
	free((*token));
	*token = lexer_get_next_token(lexer);
	if((*token)->e_type == TOKEN_STRING)
	{
		redrec->file = ft_strdup((*token)->value);
		// red->fd = open(red->file, O_RDWR | O_CREAT); //3la 7ssab type wach 4adi t ready ou la t creat
	}
	else
	{
		//free(token->value);
		printf("parse error 'missing redirection file'\n");
		redrec->e_rtype = ERROR;
	}
	return (redrec);
}

void	init_cmd1(t_token **token, t_node **tmp, t_cmd **cmd)
{
	if ((*token)->e_type == TOKEN_STRING)
	{
		(*cmd)->args = ft_lstnew((void *)
				init_arg(ft_strdup((const char *)(*token)->value)));
		ft_lstadd_back(tmp, (*cmd)->args);
	}
}

void	init_cmd2(t_token **token, t_node **tmp1, t_cmd **cmd, t_lexer *lexer)
{
	if ((*token)->e_type == TOKEN_REDICRECTION)
	{
		//system("leaks minishell");
		(*cmd)->redrec = ft_lstnew((void *)init_redirection(token, lexer));
		if (((t_redirec *)(*cmd)->redrec->content)->e_rtype == ERROR)
			return ;
		ft_lstadd_back(tmp1, (*cmd)->redrec);
		/*hena kayn leak*/
	}
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
	while ((*token) && (*token)->e_type != TOKEN_EOF
		&& (*token)->e_type != TOKEN_PIPE)
	{
		if ((*token)->e_type == TOKEN_ERROR)
			return (NULL);
		init_cmd1(token, &tmp, &cmd);
		init_cmd2(token, &tmp1, &cmd, lexer);
		free((*token)->value);
		free(*token);
		(*token) = lexer_get_next_token(lexer);
	}
	cmd->args = tmp;
	cmd->redrec = tmp1;
	return (cmd);
}
