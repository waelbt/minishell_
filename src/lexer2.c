/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:27:16 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/02 20:38:23 by waboutzo         ###   ########.fr       */
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

// token_T	*lexer_collect_quotes(lexer_T *lexer, int c, int h)
// {
// 	int		len;
// 	char	*value;
// 	char	*s;

// 	value = ft_calloc(1, sizeof(char));
// 	lexer_advance(lexer);
// 	len = get_index(*lexer, c, h);
// 	if (len < 0)
// 		return (init_token(TOKEN_ERROR, ""));
// 	while (lexer->i < len)
// 	{
// 		if (lexer->c == c)
// 			lexer_advance(lexer);
// 		s = lexer_get_current_char_as_string(lexer);
// 		value = ft_realloc(value, (ft_strlen(value)
// 					+ ft_strlen(s) + 1) * sizeof(char));
// 		ft_strcat(value, s);
// 		free(s);
// 		lexer_advance(lexer);
// 	}
// 	lexer_advance(lexer);
// 	if (count_element(value, c, ft_strlen(value)) % 2 != 0)
// 		return (init_token(TOKEN_ERROR, ""));
// 	return (init_token(TOKEN_STRING, value));
// }

token_T	*lexer_get_next_token(lexer_T *lexer)
{
	token_T	*token;

	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == 32)
			lexer_skip_whitespace(lexer);
		if(lexer->c == '|')
		{
			token = init_token(TOKEN_PIPE, lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			return token;
		}
		if(lexer->c == '<')
		{
			token = init_token(TOKEN_INPUT, lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			return token;
		}
		if(lexer->c == '>')
		{
			token = init_token(TOKEN_OUTPUT, lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			return token;
		}
		else
		{
			return lexer_collect_string(lexer, TOKEN_STRING, get_first(*lexer));
		}
	}
	return (NULL);
}

token_T	*lexer_advance_with_token(lexer_T *lexer, token_T *token)
{
	lexer_advance(lexer);
	return (token);
}
