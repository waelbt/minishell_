/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:21:38 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/12 16:37:38 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*env_var_inside_qoutes(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;

	if (!ft_isalnum(lexer->c) && (lexer->c != 34 || lexer->c != 39))
		lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	while (ft_isalnum(lexer->c) || lexer->c == '_')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	if(lexer->c == 34 || lexer->c == 39)
		lexer_previous(lexer);
	return (dollar_value(envp, value));
}

char	*quotes_cases(t_lexer *lexer, char **envp, int c)
{
	if(lexer->c == '$' && c != 39)
		return (env_var_inside_qoutes(lexer, envp));
	else
		return (lexer_get_current_char_as_string(lexer));
}
char	*quotes_handler(t_lexer *lexer, char **envp, int c)
{
	char	*value;
	char	*s;

	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	while(lexer->c != c)
	{
		s = quotes_cases(lexer, envp, c);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (value);
}