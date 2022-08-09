/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiter_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 11:54:17 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/02 11:37:23 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char	*delimiter_handle_env_var_cases(t_lexer *lexer, char **envp)
{
	if (lexer->c == '$')
		return (ft_strdup("$"));
	if (lexer->c == 34)
		return (quotes(lexer, envp,34));
	if (lexer->c == 39)
		return (quotes(lexer, envp,39));
	return (NULL);
}

char	*delimiter_handle_env_var(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;
	char	*str;
	char	*tmp;

	lexer_advance(lexer);
	str = delimiter_handle_env_var_cases(lexer, envp);
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

char	*delimiter_cases(t_lexer *lexer, char **envp)
{
	char	*str;

	if (lexer->c == '$')
		str = delimiter_handle_env_var(lexer, envp);
	else
	{
		str = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
	}
	return (str);
}

char	*delimiter(char *str, char **envp)
{
	char	*value;
	char	*s;
	char	*tmp;
	t_lexer	*lexer;

	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	lexer = init_lexer(str);
	while (lexer->c != '\0')
	{
		s = delimiter_cases(lexer, envp);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
	}
	free(lexer);
	return (value);
}
