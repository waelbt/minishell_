/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:54:17 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/31 17:06:57 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*delimiter_handle_env_var_cases(t_lexer *lexer)
{
	if (lexer->c == '$')
		return (ft_strdup("$"));
	if (lexer->c == 34)
		return (quotes(lexer, 34));
	if (lexer->c == 39)
		return (quotes(lexer, 39));
	return (NULL);
}

char	*delimiter_handle_env_var(t_lexer *lexer)
{
	char	*value;
	char	*s;
	char	*str;
	char	*tmp;

	lexer_advance(lexer);
	str = delimiter_handle_env_var_cases(lexer);
	if (str)
		return (str);
	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	while (ft_isalnum(lexer->c) || lexer->c == '_')
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
		lexer_advance(lexer);
	}
	tmp = ft_strjoin("$", value);
	free(value);
	return (tmp);
}

char	*delimiter_cases(t_lexer *lexer)
{
	char	*str;

	if (lexer->c == '$')
		str = delimiter_handle_env_var(lexer);
	else
	{
		str = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
	}
	return (str);
}

char	*delimiter(char *str)
{
	char	*value;
	char	*s;
	t_lexer	*lexer;
	char	*tmp;

	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	lexer = init_lexer(str);
	while (lexer->c != '\0')
	{
		s = delimiter_cases(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		ft_strcat(value, s);
		free(s);
	}
	free(lexer);
	return (value);
}
