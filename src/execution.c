/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:13:12 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/26 02:34:29 by lchokri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths = NULL;
	char	*path;
	int i;

	path = NULL;
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			break;
		envp++;
	}
	paths = ft_split(*envp+5, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], ft_strdup(cmd));
		if (access(paths[i], X_OK) == 0)
			path = ft_strdup(paths[i]);
		free(paths[i]);
		i++;
	}
	free(paths);
	free(cmd);
	if (path == NULL)
	{
			perror("Error");
			return (NULL);
			// exit(EXIT_FAILURE);
	}
	return (path);
}

char	*check_acces(char *cmd, char **envp)
{
	if (access(cmd, X_OK))
	{
		if(ft_strchr(cmd, '/'))
			return (NULL);
		cmd = ft_strjoin(ft_strdup("/"), cmd);
		cmd = check_cmd(cmd, envp);
		if(!cmd)
			return (NULL);
	}
	return (cmd);
}

char *join_args(t_node *head, char **env)
{
	t_args	*arg;
	char	*str;
	char	*tmp;

	if(!head)
		return (NULL);
	str = ft_strdup(((t_args *) head->content)->value);
	head = head->next;
	while (head != NULL)
	{
		arg = (t_args *) head->content;
		tmp = str;
		str = ft_strjoin(str, " ");
		free(tmp);
		tmp = str;
		str = ft_strjoin(str, arg->value);
		free(tmp);
		head = head->next;
	}
	return (str);
}

t_redirec	*get_input(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		if(tmp->e_rtype == INPUT || tmp->e_rtype == HERE_DOC)
			redrec = tmp;
		head = head->next;
	}
	return (redrec);
}

t_redirec	*get_output(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		if(tmp->e_rtype == OUTPUT || tmp->e_rtype == APPEND)
			redrec = tmp;
		head = head->next;
	}
	return (redrec);
}

void	*execution(t_node *head, char **env)
{
	t_cmd	*cmd;
	t_redirec	*input;
	t_redirec	*output;
	char	*str;
	int		status;
	int		last_fd;
	int		pipe_fd[2];
	int		id;

	last_fd = -1;
	while (head != NULL)
	{
		cmd = (t_cmd *)head->content;
		str = join_args(cmd->args, env);
		cmd->after_expand = ft_split(str, 32);
		if(cmd->after_expand)
		{
			cmd->after_expand[0] = check_acces(cmd->after_expand[0], env);
		
			if(!cmd->after_expand[0])
				return (NULL);
		}
		input = get_input(cmd->redrec);
		output = get_output(cmd->redrec);
		//printf("%d\n",output->fd);
		pipe(pipe_fd);
		id = fork();
		if(id == 0)
		{
			if(head->next != NULL)
			{
				dup2(pipe_fd[1], 1);
				close(pipe_fd[1]);
				close(pipe_fd[0]);
			}
			if(output != NULL)
			{
				dup2(output->fd, 1);
				close(output->fd);
			}
			if(last_fd != -1)
			{
				dup2(last_fd, 0);
				close(last_fd);
			}
			if(input != NULL)
			{
				dup2(input->fd, 0);
				close(input->fd);
			}
			if(cmd->after_expand)
			{
				execute(cmd->after_expand, env);
//				execve(cmd->after_expand[0], cmd->after_expand, env);
				}
			else if(!cmd->after_expand)
				exit(0);
		}
		else
		{
			if(head->next != NULL)
			{
				close(pipe_fd[1]);
			}
			if(last_fd != -1)
			{
				close(last_fd);
			}
			last_fd = pipe_fd[0];
			free(str);
		}
		head = head->next;
	}
	while (wait(&status) > 0);
	return ((void *)1);
}
