/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 18:48:37 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 18:47:59 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void   (*SIGINT_handler)(int);
// cmd_T	*init_cmd(token_T *token)
// {
// 	cmd_T *cmd;

// 	cmd = ft_calloc(1, sizeof(cmd_T));
// 	if (!cmd)
// 		return (NULL);
// 	cmd->id = 0;
// 	cmd->token = token;
// 	cmd->previous = NULL;
// 	cmd->next = NULL;
// 	return (cmd);
// }

int check_tokens(token_T *token)
{
	while(token)
	{
		if(token->type == TOKEN_ERROR)
			return (0);
		token = token->next;
	}
	return (1);
}

void print_linked_list(token_T *tokens)
{
	if(check_tokens(tokens))
	{
		while(tokens)
		{
			printf("TOKEN(%d,%s)\n", tokens->type ,tokens->value);
			tokens = tokens->next;
		}
	}
	else
		printf("error\n");
}

int count_element(char *str, char c, int len)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while(i < len)
	{
		if(str[i] == c)
			counter++;
		i++;
	}
	return counter;
}

token_T *handler(char *str)
{
	lexer_T *lexer;
	token_T *token;
	token_T *tmp;

	lexer = init_lexer(str);
	token = lexer_get_next_token(lexer);
	tmp = lexer_get_next_token(lexer);
	while(tmp != NULL)
	{
		if(tmp->type == TOKEN_ERROR)
			break;
		ft_lstadd_back(&token, tmp);
		tmp = lexer_get_next_token(lexer);
	}
	free(lexer);
	return (token);
}

int main(int argc, char **argv, char **envp)
{
	char	*str;
	token_T *token;
	(void) envp;

	if(argc == 1)
	{
		while(1)
		{
			str = readline("\033[0;35mminishell$ \033[0;37m");
			add_history (str);
			token = handler(str);
			print_linked_list(token);
			free(str);
		}
	}
	return (0);
}
