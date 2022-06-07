/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:27:16 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/07 11:35:52 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_token	*get_redirection(t_lexer *lexer)
{
	char		c;
	t_token		*tmp;
	t_token		*token;

	c = lexer->c;
	token = init_token(TOKEN_REDICRECTION,
			lexer_get_current_char_as_string(lexer));
	lexer_advance (lexer);
	if (lexer->c == c)
	{
		tmp = init_token(TOKEN_REDICRECTION,
				lexer_get_current_char_as_string(lexer));
		token->value = ft_strjoin(token->value, tmp->value);
		lexer_advance(lexer);
		free(tmp);
	}
	return (token);
}

t_token	*lexer_get_next_token(t_lexer *lexer)
{
	t_token	*token;

	while (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer_skip_whitespace(lexer);
		if (lexer->c == '|')
		{
			token = init_token(TOKEN_PIPE,
					lexer_get_current_char_as_string(lexer));
			lexer_advance(lexer);
			return (token);
		}
		else if (lexer->c == '<' || lexer->c == '>')
			return (get_redirection(lexer));
		else
			return (lexer_collect_string(lexer, TOKEN_STRING));
	}
	return (init_token(TOKEN_EOF, ""));
}

t_token	*lexer_collect_string(t_lexer *lexer, int e_type)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	if (lexer->c == '\0')
		return (init_token(TOKEN_EOF, value));
	while (lexer->c != 32 && lexer->c != '\0'
		&& lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{		
		if (lexer->c == 34)
			s = lexer_handle_quotes(lexer, 34);
		else
			s = lexer_get_current_char_as_string(lexer);
		if (!s)
			return (init_token(TOKEN_ERROR, value));
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (init_token(e_type, value));
}

int	closed_qoutes(t_lexer *lexer, char c, int *bool)
{
	if (lexer->c == c)
	{
		if (!(*bool))
			*bool = 1;
		else
		{
			*bool = 0;
			return (0);
		}
	}
	return (1);
}
