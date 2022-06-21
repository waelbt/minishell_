/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/21 18:36:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	*ft_free(t_token *token, t_lexer *lexer, t_node *node, t_node *tmp)
{
	if (!node)
		free_node(&tmp);
	free(lexer);
	free(token->value);
	free(token);
	return (node);
}

int	ft_pipe_check(t_token *token, t_token *previous)
{
	int	value;

	value = 0;
	if (ft_strchr(token->value, '|'))
		printf("parse error near `||'\n");
	else if (previous->e_type == TOKEN_PIPE && token->e_type == TOKEN_EOF)
		printf("parse error near `|'\n");
	else
		value = 1;
	free(previous->value);
	free(previous);
	return (value);
}

t_node	*handler(char *str)
{
	t_lexer	*lexer;
	t_token	*token;
	t_node	*node;
	t_node	*tmp;
	t_token	*tmp1;

	tmp = NULL;
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		if (token->e_type == TOKEN_ERROR)
			return (ft_free(token, lexer, NULL, tmp));
		node = ft_lstnew((void *) init_cmd(lexer, &token));
		if (!node)
			return (ft_free(token, lexer, NULL, tmp));
		ft_lstadd_back(&tmp, node);
		tmp1 = token;
		token = lexer_get_next_token(lexer);
		if (!ft_pipe_check(token, tmp1))
			return (ft_free(token, lexer, NULL, tmp));
	}
	return (ft_free(token, lexer, tmp, NULL));
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_node	*cmd;

	if (argc == 1)
	{
		while (1)
		{
			str = readline("\033[0;35mminishell$ \033[0;37m");
			add_history (str);
			cmd = handler(str);
			if (!(parsing(&cmd, envp)) || !(execution(cmd, envp)))
			{
				free_node(&cmd);
				free(str);
				continue ;
			}
			//printf_node(cmd);
			free_node(&cmd);
			free(str);
		}
	}
	return (0);
}
