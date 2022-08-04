/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multi_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:37:23 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/04 18:20:31 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = NULL;
	paths = ft_split(get_path(envp), ':');
	if (paths)
	{
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
	}
	if (!invalid_command_error(cmd, tmp[2], paths))
		return (NULL);
	free(paths);
	free(cmd);
	return (tmp[2]);
}

void	dup_norm(int fildes1, int fildes2)
{
	dup2(fildes1, fildes2);
	close(fildes1);
}

void	child_work(t_node *head, char **env, int *pipe_fd, int last_fd)
{
	t_cmd		*cmd;

	cmd = (t_cmd *)head->content;
	if (head->next != NULL)
		dup_norm(pipe_fd[1], 1);
	if (cmd->output != NULL)
		dup_norm(cmd->output->fd, 1);
	if (last_fd != -1)
		dup_norm(last_fd, 0);
	if (cmd->input != NULL)
		dup_norm(cmd->input->fd, 0);
	close(pipe_fd[0]);
	if (cmd->after_expand && cmd->after_expand && cmd->e_rtype == VALID)
	{
		if (!execute(cmd->after_expand, &env, 0))
		{
			check_acces(&cmd->after_expand[0], env);
			if (cmd->after_expand[0])
				execve(cmd->after_expand[0], cmd->after_expand, env);
			ft_setter(127);
		}
	}
	else
		ft_setter(0);
	exit(ft_getter());
}

void	execution_multi_cmds(t_node *head, char **env)
{
	int			last_fd;
	int			pipe_fd[2];
	int			id;
	int			res;
	int			status;
	t_cmd		*cmd;

	last_fd = -1;
	while (head != NULL)
	{
		cmd = (t_cmd *)head->content;
		pipe(pipe_fd);
		id = fork();
		if (id == 0)
		{
			signal(SIGINT, SIG_DFL);
			child_work(head, env, pipe_fd, last_fd);
		}
		else
		{
			ft_setter(0);
			if (head->next != NULL)
				close(pipe_fd[1]);
			if (last_fd != -1)
				close(last_fd);
			last_fd = pipe_fd[0];
		}
		head = head->next;
	}
	signal(SIGINT, SIG_IGN);
	res = waitpid(-1, &status, 0);
	while (res != -1)
	{
		if (res == id)
		{
			ft_setter(WEXITSTATUS(status));
			if (WIFSIGNALED(status))
				ft_setter(WTERMSIG(status) + 128);
		}
		res = waitpid(-1, &status, 0);
	}
	signal(SIGINT, sig_handler);
}
