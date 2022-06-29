/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 19:21:35 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/29 19:40:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*string_cases(t_lexer *lexer, char **envp)
{
	char	*str;

	if (lexer->c == '"')
		str = quotes_handler(lexer, envp, '"');
	else if (lexer->c == '\'')
		str = quotes_handler(lexer, envp, '\'');
	else if (lexer->c == '$')
		str = handle_env_var(lexer, envp);
	else
	{
		str = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
	}
	return (str);
}

char	*pure_arg(char *str, char **envp)
{
	char	*value;
	char	*s;
	t_lexer	*lexer;

	value = ft_calloc(1, sizeof(char));
	lexer = init_lexer(str);
	while (lexer->c != '\0')
	{
		s = string_cases(lexer, envp);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
	}
	free(str);
	free(lexer);
	return (value);
}

char	*remove_qoutes(char *str)
{
	char	*value;
	char	*s;
	t_lexer	*lexer;

	lexer = init_lexer(str);
	value = ft_calloc(1, sizeof(char));
	while (lexer->c != '\0')
	{
		if (lexer->c == '"')
			s = quotes(lexer, NULL, '"');
		else if (lexer->c == '\'')
			s = quotes(lexer, NULL, '\'');
		else
		{
			s = lexer_get_current_char_as_string(lexer);
			lexer_advance(lexer);
		}
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
	}
	free(str);
	free(lexer);
	return (value);
}

void	pure_after_expand(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = remove_qoutes(str[i]);
		i++;
	}
}

int	ft_counte_novide(char **str)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i][0] != '\0')
			counter++;
		i++;
	}
	return (counter);
}
