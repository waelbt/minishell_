/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/02 15:40:25 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//extern struct vars vr;

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

void	norm_redirection(t_redirec	*redrec, char **envp, int *index)
{
	char		*str;

	if (redrec->e_rtype != 3)
	{
		str = pure_arg(ft_strdup(redrec->file), envp);
		redrec->after_expand = advanced_split(str);
		free(str);
		redrec->path = NULL;
	}
	else
	{
		str = delimiter(redrec->file, envp);
		redrec->after_expand = advanced_split(str);
		free(str);
		str = ft_itoa(*index);
		redrec->path = ft_strjoin("/var/TMP/her_doc", str);
		free(str);
		(*index)++;
	}
}


void	*open_here_doc(t_node **head)
{
	t_node		*temporary;
	t_redirec	*redrec;

	temporary = *head;
	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		if(redrec->e_rtype == 3)
		{
			redrec->fd = open(redrec->path, O_RDONLY, 0666);
			if(redrec->fd < 0)
			{
				ft_setter(1);
				printf_error("minishell: no such file or directory: ", redrec->path, "\n");
				return (NULL);
			}
		}
		temporary = temporary->next;
	}
	return ((void *)1);
}
void	*fill_her_doc_in_fork(t_node **head, char **envp)
{
	t_node		*temporary;
	t_redirec	*redrec;
	int			status;
	int			id;

	id = fork();
	if (id != 0)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(id, &status, 0);
		if(WIFEXITED(status))
			open_here_doc(head);
		if(WIFSIGNALED(status))
		{
			signal(SIGINT, sig_handler);
			return (NULL);
		}
	}
	else
	{
		temporary = *head;
		while (temporary != NULL)
		{
			redrec = (t_redirec *) temporary->content;
			if(redrec->e_rtype == 3)
				here_doc(redrec, envp);
			temporary = temporary->next;
		}
		exit(0);
	}
	return ((void *)1);
}
void	*parsing_redrection(t_node **head, char **envp, int *index)
{
	t_node		*temporary;
	t_redirec	*redrec;

	if(!(*head))
		return ((void *)1);
	temporary = *head;
	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		norm_redirection(redrec, envp, index);
		remove_vide_string(&redrec->after_expand);
		pure_after_expand(redrec->after_expand, envp);
		if (double_pointer_len(redrec->after_expand) != 1)
		{
			ft_setter(1);
			printf_error("minishell: ", redrec->file, ": ambiguous redirect\n");
			return (NULL);
		}
		temporary = temporary->next;
	}
	if(!fill_her_doc_in_fork(head, envp))
		return (NULL);
	if(!open_file_descriptor(head))
		return (NULL);
	return ((void *)1);
}


void	parsing(t_node **command, char **envp, int *index)
{
	t_node	*temporary;
	t_cmd	*cmd;

	temporary = *command;
	while (temporary != NULL)
	{
		cmd = (t_cmd *)temporary->content;
		parsing_args(&(cmd)->args, envp);
		parsing_redrection(&(cmd)->redrec, envp, index);
		cmd->after_expand = join_args(cmd->args);
		cmd->input	= get_output_input(cmd->redrec, 0);
		cmd->output = get_output_input(cmd->redrec, 1);
		temporary = temporary->next;
	}
}
