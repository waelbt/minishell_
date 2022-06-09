/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/09 10:22:36 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
void *ft_free(t_token *token, t_lexer *lexer, t_node *node, t_node *tmp)
{
	if(!node)
		free_node(&tmp);
	free(lexer);
	free(token->value);
	free(token);
	return (node);
}
t_node	*handler(char *str)
{
	t_lexer *lexer;
	t_token *token;
	t_node	*node = NULL;
	t_node	*tmp;
	
	tmp = NULL;
	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	while (token->e_type != TOKEN_EOF)
	{
		if (token->e_type == TOKEN_ERROR)
			return (ft_free(token, lexer, NULL, tmp));
		node = ft_lstnew((void *) init_cmd(lexer, &token));
		if (!node)
			return ft_free(token, lexer, NULL, tmp);
		ft_lstadd_back(&tmp, node);
		free(token->value);
		free(token);
		token = lexer_get_next_token(lexer);
	}
	return ft_free(token, lexer, tmp, NULL);
}


//pipe handling nsito
int	main(int argc, char **argv, char **envp)
{
	char	*str;
	t_node	*cmd;

	(void) envp;
	if (argc == 1)
	{
		while (1)
		{
			str = readline("\033[0;35mminishell$ \033[0;37m");
			add_history (str);
			cmd = handler(str);
			printf_node(cmd);
			free_node(&cmd);
			free(str);
		}
	}
	return (0);
}
