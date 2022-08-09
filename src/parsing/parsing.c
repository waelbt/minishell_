/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 15:19:13 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/09 18:31:09 by waboutzo         ###   ########.fr       */
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

char *simple(t_lexer *lexer, int c)
{
	char	*value;
	char	*s;
	char	*tmp;

	lexer_advance(lexer);
	value = (char *) malloc(sizeof(char));
	value[0] =  '\0';
	while(lexer->c != c)
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
char	*get_value(char *str)
{
	t_lexer *lexer;
	char	*value;
	char	*s;
	char	*tmp;

	lexer = init_lexer(str);
	value = (char *) malloc(sizeof(char));
	value[0] =  '\0';
	while(lexer->c != '\0')
	{
		if (lexer->c == '\'' || lexer->c == '"')
			s = simple(lexer, lexer->c);
		else
		{
			s = lexer_get_current_char_as_string(lexer);
			lexer_advance(lexer);
		}
		tmp = value;
		value = ft_strjoin(value, s);
		free(tmp);
		free(s);
	}
	free(lexer);
	return (value);
}
void	remove_qoutes_delimiter(char	**str)
{
	int i;
	char	*tmp;

	i = 0;
	while(str[i])
	{
		tmp = str[i];
		str[i] = get_value(str[i]);
		free(tmp);
		i++;
	}	
}
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

	if(!(*head))
		return ((void *)1);
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
	while(temporary)
	{
		redric = (t_redirec *)temporary->content;
		if(redric->e_rtype == HERE_DOC)
			here_doc(redric, envp);
		temporary = temporary->next;
	}
}

int here_doc_counter(t_node *head)
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
			if(redrec->e_rtype == HERE_DOC)
				counter++;
			red = red->next;
		}
		head = head->next;
	}
	return (counter);
}

void	*open_heredoc_in_all_pipe_lines(t_node **head, char **envp)
{
	t_node	*temporary;
	t_cmd	*cmd;
	int		id;
	int		status;

	temporary = *head;
	if (here_doc_counter(*head) >= 17)
	{
		printf_error("minishell: maximum ", "here-document ", "count exceeded\n");
		exit(258);
	}
	id = fork();
	if (!id)
	{
		while (temporary != NULL)
		{
			cmd = (t_cmd *)temporary->content;
			open_heredoc_in_signle_cmd(&cmd->redrec, envp);
			temporary = temporary->next;
		}
		exit(0);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		waitpid(id, &status, 0);
		// if(WIFEXITED(status))
		// 	ft_setter(WEXITSTATUS(status)); //error
		if(WIFSIGNALED(status))
		{
			ft_setter(1);
			signal(SIGINT, sig_handler);
			return (NULL);
		}
	}
	return ((void *)1);
}

static int	ft_check(t_redirec *redirc)
{
	if (double_pointer_len(redirc->after_expand) != 1)
	{
		ft_setter(1);
		printf_error("minishell: ", redirc->file, ": ambiguous redirect\n");
		return (1);
	}
	if(redirc->fd < 0)
	{
		ft_setter(1);
		perror("minishell");
		return (1);
	}
	return (0);	
}
void	*open_file_descriptor(t_node **head)
{
	t_node		*temporary;
	t_redirec	*redrec;

	temporary = *head;

	while (temporary != NULL)
	{
		redrec = (t_redirec *) temporary->content;
		if (redrec->e_rtype == INPUT)
			redrec->fd = open(redrec->after_expand[0], O_RDONLY, 0666);
		else if (redrec->e_rtype == OUTPUT)
			redrec->fd = open(redrec->after_expand[0], O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (redrec->e_rtype == APPEND)
			redrec->fd = open(redrec->after_expand[0], O_WRONLY | O_APPEND | O_CREAT, 0666);
		else if (redrec->e_rtype == HERE_DOC)
			redrec->fd = open(redrec->path, O_RDONLY, 0666);
		if (ft_check(redrec))
			return (NULL);
		temporary = temporary->next;
	}
	return ((void *)1);
}

void	*parsing(t_node **command, char **envp, int *index)
{
	t_node	*temporary;
	t_cmd	*cmd;

	temporary = *command;
	while (temporary != NULL)
	{
		cmd = (t_cmd *)temporary->content;
		if (temporary != *command)
			ft_setter(0);
		parsing_args(&(cmd)->args, envp);
		parsing_redrection(&(cmd)->redrec, envp, index);
		cmd->after_expand = join_args(cmd->args);
		(*index)++;
		cmd->e_rtype = VALID;
		temporary = temporary->next;
	}
	if(!open_heredoc_in_all_pipe_lines(command, envp))
		return (NULL);
	temporary = *command;
	while (temporary != NULL)
	{
		cmd = (t_cmd *)temporary->content;
		if (!open_file_descriptor(&cmd->redrec))
			cmd->e_rtype = NOT_VALID;
		cmd->input	= get_input(cmd->redrec);
		cmd->output = get_output(cmd->redrec);
		temporary = temporary->next;
	}
	return ((void *)1);
}
