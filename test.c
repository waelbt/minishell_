/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:10:47 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/11 15:21:50 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	ft_isalnum(int c)
{
	if (c <= '9' && c >= '0' )
		return (1);
	if (c <= 122 && c >= 97)
		return (1);
	if (c <= 90 && c >= 65)
		return (1);
	return (0);
}

int		expandable(char *args)
{
		if (args[0] == 39)
			return (0);
	return (1);
}

char *handle_env_var(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;
	int status;
	
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
	return expandable(value);
}


	// if(c == 34)
	// 	return (34);
	// if(c == 39)
	// 	return (39);

else
		return (ft_strdup(""));

	}
if(c == 34 && lexer->c == '$')
			s = handle_env_var(lexer, envp);
		else

if(status != 39 && status != 34)
			return (dollar_value(envp,value));
		else
			return handle_quoutes(init_lexer(value), envp, status);