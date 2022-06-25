/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 17:13:12 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/25 18:44:20 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*get_path(char **envp)
{
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*invalid_command_error(char *cmd, char *path)
{
	if (!ft_strcmp(cmd, "/"))
	{
		free(cmd);
		printf("minishell: : command not found\n");
	}
	else if (path == NULL)
	{
		printf("minishelll: %s: command not found\n", (cmd + 1));
		free(cmd);
	}
	else
		return ((void *)1);
	return (NULL);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = NULL;
	paths = ft_split(get_path(envp), ':');
	while (paths[i++])
	{
		tmp[0] = paths[i];
		tmp[1] = ft_strdup(cmd);
		paths[i] = ft_strjoin(tmp[0], tmp[1]);
		if (access(paths[i], X_OK) == 0)
			tmp[2] = ft_strdup(paths[i]);
		free(paths[i]);
		free(tmp[0]);
		free(tmp[1]);
	}
	if (!invalid_command_error(cmd, tmp[2]))
		return (NULL);
	free(paths);
	free(cmd);
	return (tmp[2]);
}

char	*check_acces(char *cmd, char **envp)
{
	char	*tmp[2];

	if (access(cmd, X_OK))
	{
		if (ft_strchr(cmd, '/'))
			return (NULL);
		tmp[0] = ft_strdup("/");
		tmp[1] = cmd;
		cmd = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		cmd = check_cmd(cmd, envp);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}

t_redirec	*ft_close(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		close(tmp->fd);
		head = head->next;
	}
	return (redrec);
}

void	dup_norm(int fildes1, int fildes2)
{
	dup2(fildes1, fildes2);
	close(fildes1);
}

void	child_work(t_node *head, char **env, int *pipe_fd, int last_fd)
{
	t_cmd		*cmd;
	t_redirec	*input;
	t_redirec	*output;
	char		**after_expand;

	cmd = (t_cmd *)head->content;
	after_expand = ft_spilt_beta(cmd->args);
	if (after_expand)
		after_expand[0] = check_acces(after_expand[0], env);
	input = get_output_input(cmd->redrec, 1);
	output = get_output_input(cmd->redrec, 0);
	if (head->next != NULL)
		dup_norm(pipe_fd[1], 1);
	if (output != NULL)
		dup_norm(output->fd, 1);
	if (last_fd != -1)
		dup_norm(last_fd, 0);
	if (input != NULL)
		dup_norm(input->fd, 0);
	close(pipe_fd[0]);
	ft_close(cmd->redrec);
	if (after_expand && after_expand[0])
		execve(after_expand[0], after_expand, env);
	exit(0);
}

void	*execution(t_node *head, char **env)
{
	int		last_fd;
	int		pipe_fd[2];
	int		id;

	last_fd = -1;
	while (head != NULL)
	{
		pipe(pipe_fd);
		id = fork();
		if (id == 0)
			child_work(head, env, pipe_fd, last_fd);
		else
		{
			if (head->next != NULL)
				close(pipe_fd[1]);
			if (last_fd != -1)
				close(last_fd);
			ft_close(((t_cmd *)head->content)->redrec);
			last_fd = pipe_fd[0];
		}
		head = head->next;
	}
	while (wait(NULL) > 0)
		;
	return ((void *)1);
}
