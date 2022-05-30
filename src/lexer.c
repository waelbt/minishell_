/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/30 10:21:58 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

lexer_T	*init_lexer(char *contents)
{
	lexer_T	*lexer;

	lexer = ft_calloc(1, sizeof(lexer_T));
	if (!lexer)
		return (NULL);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(lexer_T	*lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_T	*lexer)
{
	while (lexer->c == 32)
		lexer_advance(lexer);
}

char	*lexer_get_current_char_as_string(lexer_T	*lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

token_T	*lexer_collect_string(lexer_T *lexer, int c)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	if (lexer->c == '\0')
		return (NULL);
	while (lexer->c != c && lexer->c != '\0')
	{
		while (lexer->c == 39 || lexer->c == '"' || lexer->c == '$')
			lexer_advance(lexer);
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (init_token(TOKEN_STRING, value));
}
