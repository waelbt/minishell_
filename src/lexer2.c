/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 16:27:16 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 21:51:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	norm(t_lexer lexer, int c, int s)
{
	if (!(lexer.contents[lexer.i + 1] == 32
			|| lexer.contents[lexer.i + 1] == '\0'
			|| lexer.contents[lexer.i + 1] == s))
		return (1);
	return (0);
}

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
	return (NULL);
}

t_token	*lexer_collect_string(t_lexer *lexer, int e_type)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	if (lexer->c == '\0')
		return (NULL);
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
