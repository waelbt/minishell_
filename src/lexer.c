/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/25 19:16:39 by waboutzo          #+#    #+#             */
/*   Updated: 2022/05/29 15:51:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


lexer_T	*init_lexer(char* contents)
{
	lexer_T *lexer;

	lexer = ft_calloc(1, sizeof(lexer_T));
	if(!lexer)
		return (NULL);
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	
	return (lexer);
}

void	lexer_advance(lexer_T* lexer)
{
	if(lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

void	lexer_skip_whitespace(lexer_T* lexer)
{
	while(lexer->c == 32)
		lexer_advance(lexer);
}

char	*lexer_get_current_char_as_string(lexer_T* lexer)
{
	char *str;

	str = ft_calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';
	return (str);
}

// token_T	*lexer_get_next_token(lexer_T *lexer)
// {
	
// }
// int check_d(char *str, int c)
// {
// 	int i;
// 	int counter;

// 	i = 0;
// 	counter = 0;
// 	while(str[i] != '\0' || (str[i] != c && str[i + 1] != 32))
// 	{
// 		if(str[i] == c)
// 			counter++;
// 		if(str[i] == '\0')
// 			break ;
// 		i++;
// 	}
// 	printf("%d\n", counter);
// 	if(counter % 2 != 0 && counter != 0)
// 			return 1;
// 	return 0;
// }


token_T	*lexer_collect_string(lexer_T *lexer, int c)
{
	char	*value;
	char *s;

	value = ft_calloc(1 ,sizeof(char));
	value[0] = '\0';
	if(lexer->c == '\0')
		return NULL;
	while (lexer->c != c && lexer->c != '\0')
	{
		if(lexer->c == 39 || lexer->c == '"')
			lexer_advance(lexer);
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	// free(s);
	return init_token(TOKEN_STRING, value);
	
}


int get_index(lexer_T lexer, int c, int s)
{
	int index;

	index = 0;
	while(lexer.c != '\0')
	{
		if(lexer.c == c)
		{
			if(lexer.contents[lexer.i - 1] == 32)
				return (-1);
			if(lexer.contents[lexer.i + 1] == 32 || lexer.contents[lexer.i + 1] == '\0')
				return (lexer.i);
			if(!(lexer.contents[lexer.i + 1] == 32 || lexer.contents[lexer.i + 1] == '\0' || lexer.contents[lexer.i + 1] == s))
			{
				while (!(lexer.contents[lexer.i + 1] == 32 || lexer.contents[lexer.i + 1] == '\0' || lexer.contents[lexer.i + 1] == s))
					lexer_advance(&lexer);
				return (lexer.i + 1);
			}
		}
		lexer_advance(&lexer);
	}
	if(lexer.contents[lexer.i - 1] != c)
		return (-1);
	return (index);
}
token_T	*lexer_collect_quotes(lexer_T *lexer, int c, int h)
{
	int len;
	char	*value;
	char *s;

	value = ft_calloc(1 ,sizeof(char));
	// value[0] = '\0';
	lexer_advance(lexer);
	len = get_index(*lexer, c, h);
	// if(!check_d(&lexer->contents[lexer->i], c))
	// 	return init_token(TOKEN_ERROR, value);
	if(len < 0)
		return init_token(TOKEN_ERROR, "");
	// printf("%d\n",get_index(*lexer, c, h));
	// if(count_element(&lexer->contents[lexer->i], c, len) % 2 == 0)
	// 	return init_token(TOKEN_ERROR, "");;
	while (lexer->i < len)
	{
		if(lexer->c == c)
			lexer_advance(lexer);
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value) + ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
		// if(lexer->c == '\0')
		// 	break ;
	}
	lexer_advance(lexer);
	// free(s);
	if(count_element(value, c, ft_strlen(value)) % 2 != 0)
		return init_token(TOKEN_ERROR, "");
	return init_token(TOKEN_STRING, value);
	
}

token_T	*lexer_get_next_token(lexer_T *lexer)
{
	while(lexer->c != '\0' && lexer->i < ft_strlen(lexer->contents))
	{
		if (lexer->c == 32)
			lexer_skip_whitespace(lexer);
		if(lexer->c == '"')
			return lexer_collect_quotes(lexer, '"', 39);
		if(lexer->c == 39)
			return lexer_collect_quotes(lexer, 39, '"');
		else
			return lexer_collect_string(lexer, ' ');
	}
	return NULL;
}

token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token)
{
	lexer_advance(lexer);
	return token;
}

// if(lexer->c == h)
// {
// 	if(!check_d(&lexer->contents[lexer->i + 1], h))
// 		return init_token(TOKEN_ERROR, value);
// }