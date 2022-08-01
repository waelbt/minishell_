/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 15:03:03 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/01 12:47:46 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_token	*init_token(int type, char *value)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	token->e_type = type;
	token->value = value;
	return (token);
}

t_node	*handler(t_lexer *lexer)
{
	t_token	*token[2];
	t_node	*node[2];

	node[1] = NULL;
	token[0] = lexer_get_next_token(lexer);
	if (!ft_strcmp(token[0]->value, "|"))
	{
		ft_setter(258);
		printf_error(NULL, "parse error near `|'\n", NULL);
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
