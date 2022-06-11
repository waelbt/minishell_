/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:01 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/11 18:34:44 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*dollar_inside_qoutes(t_lexer *lexer, char **envp, int c)
{
	char	*str;

	if (lexer->c == '$' && c == 34)
	{
		str = handle_env_var(lexer, envp);
		lexer_previous(lexer);
		return (str);
	}
	else
		return (lexer_get_current_char_as_string(lexer));
}

char	*handle_env_var(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;

	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	if (lexer->c == 34)
		return (handle_quoutes(lexer, envp, 34));
	if (lexer->c == 39)
		return (handle_quoutes(lexer, envp, 39));
	if (!ft_isalnum(lexer->c))
		lexer_advance(lexer);
	while (ft_isalnum(lexer->c) || lexer->c == '_')
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

int		find_char(char *s, char c)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*dollar_value(char **envp, char *var)
{
	if (!(find_char(var, '=')) && *var)
	{
		while (*envp)
		{
			if(!strncmp(*envp, var, ft_strlen(var)))
				return (ft_strdup(*envp+ft_strlen(var)+1));
			envp++;
		}
	}
	return (ft_strdup(""));
}
