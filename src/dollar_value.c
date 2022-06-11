/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 17:53:01 by lchokri           #+#    #+#             */
/*   Updated: 2022/06/11 18:33:20 by waboutzo         ###   ########.fr       */
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
