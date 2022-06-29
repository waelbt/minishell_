/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/29 18:27:55 by waboutzo         ###   ########.fr       */
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

char	**remove_vide_string(char **str)
{
	char	**ptr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ptr = (char **)malloc((ft_counte_novide(str) + 1) * sizeof(char *));
	while (str[i])
	{
		if (str[i][0] != '\0')
			ptr[j++] = ft_strdup(str[i]);
		i++;
	}
	ptr[j] = NULL;
	free_double_char(str);
	return (ptr);
}

void	parsing_args(t_node **head, char **envp)
{
	t_node		*temporary;
	t_args		*args;

	temporary = *head;
	while (temporary != NULL)
	{
		args = (t_args *) temporary->content;
		args->after_expand = advanced_split(
				pure_arg(ft_strdup(args->value), envp));
		args->after_expand = remove_vide_string(args->after_expand);
		pure_after_expand(args->after_expand);
		temporary = temporary->next;
	}
}

void	norm_redirection(t_redirec	*redrec, char **envp)
{
	if (redrec->e_rtype != 3)
		redrec->after_expand = advanced_split(
				pure_arg(ft_strdup(redrec->file), envp));
	else
		redrec->after_expand = advanced_split(
				delimiter(redrec->file, envp));
}
void	*parsing_redrection(t_node **head, char **envp, int *index)
{
	t_node		*temporary;
	t_redirec	*redrec;

	temporary = *head;
	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		norm_redirection(redrec, envp);
		redrec->after_expand = remove_vide_string(redrec->after_expand);
		if (double_pointer_len(redrec->after_expand) != 1)
		{
			printf("minishell: %s: ambiguous redirect\n", redrec->file);
			return (NULL);
		}
		redrec->fd = open_file_descriptor(redrec, envp, index);
		if (redrec->fd < 0)
		{
			printf("Error\n");
			return (NULL);
		}
		temporary = temporary->next;
	}
	return ((void *)1);
}

void	*parsing(t_node **command, char **envp, int *index)
{
	t_node	*temporary;

	temporary = *command;
	while (temporary != NULL)
	{
		parsing_args(&((t_cmd *)temporary->content)->args, envp);
		if (!parsing_redrection(&((t_cmd *)temporary->content)->redrec, envp, index))
			return (NULL);
		temporary = temporary->next;
	}
	return ((void *)1);
}
