/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/29 20:00:18 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

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
	free_double_char(str, 0);
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
		pure_after_expand(redrec->after_expand);
		if (double_pointer_len(redrec->after_expand) != 1)
		{
			printf("minishell: %s: ambiguous redirect\n", redrec->file);
			return (NULL);
		}
		redrec->fd = open_file_descriptor(redrec, envp, index);
		if (redrec->fd < 0)
		{
			printf("minishell: no such file or directory: %s\n",
				redrec->after_expand[0]);
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
		if (!parsing_redrection(
				&((t_cmd *)temporary->content)->redrec, envp, index))
			return (NULL);
		temporary = temporary->next;
	}
	return ((void *)1);
}
