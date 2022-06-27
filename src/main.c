/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/27 02:44:31 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// extern int errno ;

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

t_node	*handler(t_lexer *lexer)
{
	t_token	*token[2];
	t_node	*node[2];

	node[1] = NULL;
	token[0] = lexer_get_next_token(lexer);
	if (!ft_strcmp(token[0]->value, "|"))
	{
		printf("parse error near `|'\n");
		return (ft_free(token[0], lexer, NULL, node[1]));
	}
	while (token[0]->e_type != TOKEN_EOF)
	{
		if (token[0]->e_type == TOKEN_ERROR)
			return (ft_free(token[0], lexer, NULL, node[1]));
		node[0] = ft_lstnew((void *) init_cmd(lexer, &token[0]));
		if (!node[0])
			return (ft_free(token[0], lexer, NULL, node[1]));
		ft_lstadd_back(&node[1], node[0]);
		token[1] = token[0];
		token[0] = lexer_get_next_token(lexer);
		if (!ft_pipe_check(token[0], token[1]))
			return (ft_free(token[0], lexer, NULL, node[1]));
	}
	return (ft_free(token[0], lexer, node[1], NULL));
}

void	sig_handler()
{
	printf("we caught a signal!!!\n");
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**env;
	t_node	*cmd;
	int		index;
	int		sig;

	sig = 1;
	env = my_envp(envp);
	index = 0;
	if (argc == 1)
	{
			while (sig <= 31)
			{
				signal(sig, sig_handler);
				sig++;
			}
		while (1)
		{
		str = readline("\033[0;35mminishell$ \033[0;37m");
			add_history (str);
			cmd = handler(init_lexer(str));
			if (parsing(&cmd, env, &index))
				execution(cmd, env);
			ft_unlik(&index);
			free_node(&cmd);
			free(str);
		}
	}
	return (0);
}
