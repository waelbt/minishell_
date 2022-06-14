# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    readme.txt                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/14 11:35:00 by waboutzo          #+#    #+#              #
#    Updated: 2022/06/14 15:21:29 by waboutzo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

lexer->c == '$'
	dollar_parsing : 
		lexer_advance(lexer);
		if(lexer->c == '\0')
			$
		if(lexer->c == '"' || lexer->c == '\'')
			quotes_handler
		if(lexer->c == '$')
			$
		if(lexer->c not alpha numric  && lexer->c != '_')
			$ lexer->c
		if(lexer->c numric)
			skip $ lexer->c


	char *str;

	if (lexer->i == next_qoutes)
		return (ft_strdup("$"));
	if (!ft_isalnum(lexer->c))
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
			return (ft_strdup("minishell"));
		}
		lexer_advance(lexer);
		return (lexer_get_current_char_as_string(lexer));
	}
	return (NULL);
}

if (lexer->c == '$' && c != 39)
	{
		str = env_var_inside_qoutes(lexer, envp, c);
		lexer_previous(lexer);
		return (str);
	}

dawdawddawdawdwaboutzo$+dawaUSERUSER$