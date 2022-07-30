/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 12:52:38 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/30 03:48:49 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*hard_code(t_lexer *lexer, char **envp, int c, int next_qoutes)
{
	char	*str;
	char	*tmp;

	if (lexer->c == '$' || lexer->i == next_qoutes)
		return (ft_strdup("$"));
	else
		return (ft_norm(lexer));
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
	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->i != next_qoutes
		&& (ft_isalnum(lexer->c) || lexer->c == '_'))
	{
		s = lexer_get_current_char_as_string(lexer);
		str = value;
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		free(str);
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	char *tmp =  dollar_value(envp, value);
	free(value);
	return tmp;
}

char	*quotes_cases(t_lexer *lexer, char **envp, int c)
{
	char	*str;

	if (lexer->c == '$' && c != 39)
		str = env_var_inside_qoutes(lexer, envp, c);
	else
	{
		str = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
	}
	return (str);
}

int	get_end(t_lexer lexer, int c)
{
	int	c_counter;

	c_counter = 0;
	while (c_counter != 2)
	{
		if (lexer.c == c)
			c_counter++;
		lexer_advance(&lexer);
	}
	return (lexer.i);
}

char	*quotes_handler(t_lexer *lexer, char **envp, int c)
{
	char	*value;
	char	*s;
	int		stop_point;
	char	*tmp;

	stop_point = get_end(*lexer, c);
	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->i < stop_point)
	{
		s = quotes_cases(lexer, envp, c);
		tmp = value;
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		free(tmp);
		ft_strcat(value, s);
		free(s);
	}
	return (value);
}
