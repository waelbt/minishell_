/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 16:02:05 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*init_lexer(char *contents)
{
	t_lexer	*lexer;

	if (!contents)
		return (NULL);
	lexer = ft_calloc(1, sizeof(t_lexer));
	if (!lexer)
		return (NULL);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return (lexer);
}

void	lexer_advance(t_lexer	*lexer)
{
	if (lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(t_lexer *lexer)
{
	while (lexer->c == 32)
		lexer_advance(lexer);
}

char	*lexer_get_current_char_as_string(t_lexer	*lexer)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

char	*lexer_handle_quotes(t_lexer *lexer, int c)
{
	char	*value;
	char	*s;
	int		close_quote;
	char	*tmp;

	close_quote = 0;
	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->c != '\0')
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
		if (!closed_qoutes(lexer, c, &close_quote))
			break ;
		lexer_advance(lexer);
	}
	if (lexer->c == '\0')
	{
		free(value);
		return (NULL);
	}
	return (value);
}
