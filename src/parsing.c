/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/11 16:53:39 by waboutzo         ###   ########.fr       */
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

char *dollar_inside_qoutes(t_lexer *lexer, char **envp, int c)
{
	char	*str;

	if(lexer->c == '$' && c == 34)
	{
		str = handle_env_var(lexer, envp);
		lexer_previous(lexer);
		return (str);
	}
	else
		return (lexer_get_current_char_as_string(lexer));
}
char *handle_quoutes(t_lexer *lexer, char **envp, int c)
{
	char	*value;
	char	*s;
	
	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	while (lexer->c != c)
	{
		s = dollar_inside_qoutes(lexer, envp, c);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (value);
}

char *handle_env_var(t_lexer *lexer, char **envp)
{
	char	*value;
	char	*s;
	
	lexer_advance(lexer);
	value = ft_calloc(1, sizeof(char));
	if(lexer->c == 34)
		return handle_quoutes(lexer, envp, 34);
	if(lexer->c == 39)
		return handle_quoutes(lexer, envp, 39);
	while (ft_isalnum(lexer->c) || lexer->c == '_')
	{
		s = lexer_get_current_char_as_string(lexer);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	return (dollar_value(envp,value));
}

char *string_cases(t_lexer *lexer, char **envp)
{
	if(lexer->c == '$')
		return handle_env_var(lexer, envp);
	if(lexer->c == '"')
		return handle_quoutes(lexer, envp,'"');
	if(lexer->c == '\'')
		return handle_quoutes(lexer, envp,'\'');
	else 
		return (lexer_get_current_char_as_string(lexer));
}
char	*pure_arg(char *str, char **envp)
{
	char	*value;
	char	*s;
	t_lexer *lexer;
	
	value = ft_calloc(1, sizeof(char));
	lexer = init_lexer(str);
	while (lexer->c != '\0')
	{
		s = string_cases(lexer, envp);
		value = ft_realloc(value, (ft_strlen(value)
					+ ft_strlen(s) + 1) * sizeof(char));
		ft_strcat(value, s);
		free(s);
		lexer_advance(lexer);
	}
	free(str);
	free(lexer);
	return value;
}

void	parsing_args(t_node **head, char **envp)
{
	t_node		*temporary;
	t_args		*args;

	temporary = *head;
	while (temporary != NULL)
	{
		args = (t_args *) temporary->content;
		args->value = pure_arg(args->value, envp);
		temporary = temporary->next;
	}
}

void	parsing(t_node **command, char **envp)
{
	t_node	*temporary;

	temporary = *command;
	while (temporary != NULL)
	{
		parsing_args(&((t_cmd *)temporary->content)->args, envp);
		// parsing_redrection(&((t_cmd *)temporary->content)->redrec);
		temporary = temporary->next;
	}
}

// void parsing_redrection(t_node **head)
// {
// 	t_node		*temporary;

// 	temporary = *head;
// 	while (temporary != NULL)
// 	{
// 		temporary = temporary->next;
// 	}
// }

// int		i;
// 	char	*tmp;
// 	char	*expd;

// 	tmp = *str;
// 	i = 0;
// 	while (tmp[i])
// 	{
// 		if (tmp[i] == '$')
// 		{
// 			expand_dollar(tmp, &expd, i);
// 			free(expd);
// 		}
// 		i++;
// 	}
