/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:27:16 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 18:43:20 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	norm(lexer_T lexer, int c, int s)
{
	if (!(lexer.contents[lexer.i + 1] == 32
			|| lexer.contents[lexer.i + 1] == '\0'
			|| lexer.contents[lexer.i + 1] == s))
		return (1);
	return (0);
}

token_T	*lexer_get_next_token(lexer_T *lexer)
{
	token_T	*token;
	token_T	*tmp;
	char c;

	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer_skip_whitespace(lexer);
		if(lexer->c == '|')
		{
			token = init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			return token;
		}
		else if(lexer->c == '<' || lexer->c == '>')
		{
			c = lexer->c;
			token = init_token(TOKEN_REDICRECTION, lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			if(lexer->c == c)
			{
				tmp = init_token(TOKEN_REDICRECTION, lexer_get_current_char_as_string(lexer));
				token->value = ft_strjoin(token->value, tmp->value);
				lexer_advance(lexer);
			}
			return token;
		}
		else
			return lexer_collect_string(lexer, TOKEN_STRING);
	}
	return (NULL);
}

token_T	*lexer_advance_with_token(lexer_T *lexer, token_T *token)
{
	lexer_advance(lexer);
	return (token);
}
