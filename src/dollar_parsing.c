/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 13:12:20 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/14 15:49:08 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"
// void	lexer_previous(t_lexer	*lexer)
// {
// 	if (lexer->i != 0)
// 	{
// 		lexer->i -= 1;
// 		lexer->c = lexer->contents[lexer->i];
// 	}
// }

char	*hard_code_norm(t_lexer *lexer, char **envp)
{
	char *str;

	if(lexer->c == '$')
		return ft_strdup("$");
	if (lexer->c == 34)
		return (quotes_handler(lexer, envp, 34));
	if (lexer->c == 39)
		return (quotes_handler(lexer, envp, 39));
	if (!ft_isalnum(lexer->c) && lexer->c != '_')
	{
		str = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
		return (ft_strjoin("$", str));
	}
	if (ft_isdigit(lexer->c))
	{
		if(lexer->c == '0')
		{
			lexer_advance(lexer);
			return ft_strdup("minishell");
		}
		lexer_advance(lexer);
		return ft_strdup("");
	}
	return (NULL);
}

char	*handle_env_var(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;
	char	*str;

	lexer_advance(lexer);
	str = hard_code_norm(lexer, envp);
	if (str)
		return (str);
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
	return (dollar_value(envp, value));
}

void	free_double_char(char **tmp)
{
	int	i;

	i = 0;
	while (tmp[i])
	{
		free(tmp[i]);
		i++;
	}
	free(tmp);
}

char	*dollar_value(char **envp, char *var)
{
	char	*str;
	char	**tmp;

	if (!(find_char(var, '=')) && *var)
	{
		while (*envp)
		{
			tmp = ft_split(*envp, '=');
			if (!ft_strcmp(tmp[0], var))
			{
				str = ft_strdup(tmp[1]);
				free(var);
				free_double_char(tmp);
				return (str);
			}
			free_double_char(tmp);
			envp++;
		}
	}
	free(var);
	return (ft_strdup(""));
}
