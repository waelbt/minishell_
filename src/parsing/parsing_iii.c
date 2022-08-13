/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_iii.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 16:28:24 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/13 23:04:26 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	norm_redirection(t_redirec	*redrec, char **envp, int *index)
{
	char		*str;

	redrec->fd = 0;
	if (redrec->e_rtype != 3)
	{
		if (redrec->e_rtype == OUTPUT || redrec->e_rtype == APPEND)
			redrec->fd = 1;
		str = pure_arg(ft_strdup(redrec->file), envp);
		redrec->after_expand = advanced_split(str);
		remove_vide_string(&redrec->after_expand);
		pure_after_expand(redrec->after_expand, envp);
		free(str);
		redrec->path = NULL;
	}
	else
	{
		redrec->after_expand = advanced_split(redrec->file);
		remove_qoutes_delimiter(redrec->after_expand);
		str = ft_itoa(*index);
		redrec->path = ft_strjoin("/var/TMP/her_doc", str);
		free(str);
	}
}

void	*parsing_redrection(t_node **head, char **envp, int *index)
{
	t_node		*temporary;
	t_redirec	*redrec;

	temporary = *head;
	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		norm_redirection(redrec, envp, index);
		(*index)++;
		temporary = temporary->next;
	}
	return ((void *)1);
}

void	open_heredoc_in_signle_cmd(t_node **head, char **envp)
{
	t_node		*temporary;
	t_redirec	*redric;

	temporary = *head;
	while (temporary)
	{
		redric = (t_redirec *)temporary->content;
		if (redric->e_rtype == HERE_DOC)
			here_doc(redric, envp);
		temporary = temporary->next;
	}
}

int	here_doc_counter(t_node *head)
{
	t_redirec	*redrec;
	t_node		*red;
	int			counter;

	counter = 0;
	while (head != NULL)
	{
		red = ((t_cmd *)head->content)->redrec;
		while (red != NULL)
		{
			redrec = (t_redirec *)red->content;
			if (redrec->e_rtype == HERE_DOC)
				counter++;
			red = red->next;
		}
		head = head->next;
	}
	return (counter);
}

int	ft_check_ambiguous(t_redirec *redirc)
{
	char	*str;

	str = "minishell: ";
	if (double_pointer_len(redirc->after_expand) != 1)
	{
		ft_setter(1);
		printf_error("minishell: ", redirc->file, ": ambiguous redirect\n");
		return (1);
	}
	if (redirc->fd < 0)
	{
		ft_setter(1);
		str = ft_strjoin(str, redirc->file);
		perror(str);
		free(str);
		return (1);
	}
	return (0);
}
