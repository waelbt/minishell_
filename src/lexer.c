/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/03 18:57:25 by waboutzo         ###   ########.fr       */
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

int ft_counter(lexer_T lexer, int c)
{
	int counter;

	counter = 0;
	while(lexer.c != '\0')
	{
		if(lexer.c == c)
			counter++;
		lexer_advance(&lexer);
	}
	return counter;
}

int get_index(lexer_T lexer, int c)
{
	while(lexer.c != '\0')
	{
		if(lexer.c == c)
			return (lexer.i);
		lexer_advance(&lexer);
	}
	return (lexer.i);
}

int get_first(lexer_T lexer)
{
	while(lexer.c != '\0')
	{
		if (lexer.c == 34)
			return (34);
		if (lexer.c == 39)
			return (39);
		lexer_advance(&lexer);
	}
	return (0);
}

int get_quotes_index(lexer_T lexer, int c, int index)
{
	int h;
	lexer.i = index;
	lexer.c = lexer.contents[lexer.i];
	lexer_advance(&lexer);
	h = (((c == 34) * 39) + ((c == 39) * 34));
	while (lexer.c != '\0')
	{
		if(lexer.c == c)
		{
			lexer_advance(&lexer);
			if(lexer.c == h)
			{
				if((ft_counter(lexer, h) % 2))
					return (-1);
				else
					return (lexer.i - 1);
			}
			if(lexer.c == c)
				return (lexer.i - 1);
			if(lexer.c == 32 || lexer.c == '\0')
				return (lexer.i - 1);
			while(lexer.c != 32 && lexer.c != '\0')
			{
				// printf("%c",lexer.c);
				lexer_advance(&lexer);
			}
			return (lexer.i);
		}
		lexer_advance(&lexer);
	}
	return (0);
}
token_T	*lexer_collect_string(lexer_T *lexer, int type, int c)
{
	char	*value;
	char	*s;
	int		len;
	int		i[2];

	value = ft_calloc(1, sizeof(char));
	value[0] = '\0';
	len = 0;
	if (lexer->c == '\0')
		return (NULL);
	i[0] = get_index(*lexer, 32);
	if(c == 0)
		len = get_index(*lexer, 32);
	else
	{
		len = get_quotes_index(*lexer, c, get_index(*lexer, c)) + 1;
		if(ft_counter(*lexer, c) % 2 || len <= 0)
		{
			return (init_token(TOKEN_ERROR, value));
		}
	}
	// printf(len);
	while (lexer->i < len && lexer->c != '\0' && lexer->c != '|' && lexer->c != '<' && lexer->c != '>')
	{
		// printf("%d %c\n",len,lexer->c);
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	//printf("%c\n", lexer->c);
	//printf("1lexer->c: %c , lexer->i: %d\n", lexer->c, lexer->i);
	//lexer_advance(lexer);
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