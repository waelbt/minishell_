/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iv.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:25:14 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 17:04:02 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	remove_vide_string(char ***s)
{
	char	**ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = (char **)malloc((ft_counte_novide(*s) + 1) * sizeof(char *));
	while ((*s)[i])
	{
		if ((*s)[i][0] != '\0')
			ptr[j++] = ft_strdup((*s)[i]);
		i++;
	}
	ptr[j] = NULL;
	free_double_char(*s, 0);
	*s = ptr;
}

void	parsing_args(t_node **head, char **envp)
{
	t_node		*temporary;
	t_args		*args;
	char		*tmp;

	temporary = *head;
	while (temporary != NULL)
	{
		args = (t_args *) temporary->content;
		tmp = pure_arg(ft_strdup(args->value), envp);
		args->after_expand = advanced_split(tmp);
		free(tmp);
		remove_vide_string(&args->after_expand);
		pure_after_expand(args->after_expand, envp);
		temporary = temporary->next;
	}
}

char	*simple(t_lexer *lexer, int c)
{
	char	*value;
	char	*s;
	char	*tmp;

	lexer_advance(lexer);
	value = (char *) malloc(sizeof(char));
	value[0] = '\0';
	while (lexer->c != c)
	{
		s = lexer_get_current_char_as_string(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer);
	return (value);
}

char	*delimiter_cases(t_lexer *lexer)
{
	char	*s;

	if (lexer->c == '$')
	{
		if (lexer->contents[lexer->i + 1] == 34
			|| lexer->contents[lexer->i + 1] == 39)
			lexer_advance(lexer);
	}
	if (lexer->c == '\'' || lexer->c == '"')
		return (simple(lexer, lexer->c));
	else
	{
		s = lexer_get_current_char_as_string(lexer);
		lexer_advance(lexer);
		return (s);
	}
}

char	*get_value(char *str)
{
	t_lexer	*lexer;
	char	*value;
	char	*s;
	char	*tmp;

	lexer = init_lexer(str);
	value = (char *) ft_calloc(1, sizeof(char));
	while (lexer->c != '\0')
	{
		s = delimiter_cases(lexer);
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
	}
	free(lexer);
	return (value);
}
