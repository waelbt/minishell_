/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qoutes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 15:21:38 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/13 07:37:29 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	get_index(t_lexer lexer, char c)
{
	while (lexer.c != '\0')
	{
		if (lexer.c == c)
			return (lexer.i);
		lexer_advance(&lexer);
	}
	return (-1);
}

char	*hard_code(t_lexer *lexer, char **envp, int c, int next_qoutes)
{
	if (lexer->i == next_qoutes)
		return (ft_strdup("$"));
	if (!ft_isalnum(lexer->c) && lexer->c != 42)
		return (ft_strjoin("$", lexer_get_current_char_as_string(lexer)));
	if (ft_isdigit(lexer->c))
	{
		lexer_advance(lexer);
		return (lexer_get_current_char_as_string(lexer));
	}
	return (NULL);
}

char	*env_var_inside_qoutes(t_lexer *lexer, char **envp, int c)
{
	char	*value;
	char	*s;
	char	*str;
	int		next_qoutes;

	lexer_advance(lexer);
	next_qoutes = get_index(*lexer, c);
	str = hard_code(lexer, envp, c, next_qoutes);
	if (str)
		return (str);
	value = ft_calloc(1, sizeof(char));
	while (lexer->i != next_qoutes
		&& (ft_isalnum(lexer->c) || lexer->c == '_'))
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (dollar_value(envp, value));
}

char	*quotes_cases(t_lexer *lexer, char **envp, int c)
{
	char	*str;

	if (lexer->c == '$' && c != 39)
	{
		str = env_var_inside_qoutes(lexer, envp, c);
		lexer_previous(lexer);
		return (str);
	}
	else
		return (lexer_get_current_char_as_string(lexer));
}

char	*quotes_handler(t_lexer *lexer, char **envp, int c)
{
	char	*value;
	char	*s;

	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	while (lexer->c != c)
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
