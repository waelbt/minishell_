/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/04 18:48:43 by waboutzo         ###   ########.fr       */
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


char *lexer_handle_quotes(lexer_T *lexer, int c)
{
	char	*value;
	char	*s;
	int close_quote = 0;

	value = ft_calloc(1, sizeof(char));
	while(lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		// printf("%s\n",s);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		if(lexer->c == c)
		{
			if(!close_quote)
				close_quote = 1;
			else
			{
				close_quote = 0;
				break;
			}
		}
		lexer_advance(lexer);
	}
	if(lexer->c == '\0')
		return (NULL);
	return  (value);
}
token_T	*lexer_collect_string(lexer_T *lexer, int type)
{
	char	*value;
	char	*s;

	value = ft_calloc(1, sizeof(char));
	//&& lexer->c != '|' && lexer->c != '<' && lexer->c != '>'
	if(lexer->c == '\0')
		return (NULL);
	while (lexer->c != 32 && lexer->c != '\0' && lexer->c != '<' && lexer->c != '>' && lexer->c != '|')
	{		
		if(lexer->c == 34)
			s = lexer_handle_quotes(lexer, 34);
		else
			s = lexer_get_current_char_as_string(lexer);
		if(!s)
			return init_token(TOKEN_ERROR, value);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (init_token(type, value));
}


// if (lexer->c == 32)
// 			lexer_skip_whitespace(lexer);
// 		if (lexer->c == 34)
// 			return (lexer_collect_quotes(lexer, 34, 39));
// 		if (lexer->c == 39)
// 			return (lexer_collect_quotes(lexer, 39, 34));
// 		// if (lexer->c == '$')
// 		// 	return (lexer_collect_quotes(lexer, 39, '"'));
// 		else
// 			return (lexer_collect_string(lexer));