/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_multi_commands.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:37:23 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/12 16:05:47 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_execve(t_cmd *cmd, char **env)
{
	char		*path;

	error_handling(cmd->after_expand[0]);
	path = check_cmd(cmd->after_expand[0], env);
	execve(path, cmd->after_expand, env);
	perror("minishell");
	ft_setter(127);
}

void	child_work(t_node *head, char **env, int *pipe_fd, int last_fd)
{
	t_cmd		*cmd;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
	if (cmd->after_expand && cmd->after_expand[0] && cmd->e_rtype == VALID)
	{
		save_pwd(cmd->after_expand[0]);
		if (!is_built_ins(cmd->after_expand, &env, 0))
			ft_execve(cmd, env);
	}
	else
		ft_setter(0);
	exit(ft_getter());
}

void	parent_work(t_node *head, int *last_fd, int *pipe_fd)
{
	t_cmd		*cmd;

	cmd = (t_cmd *)head->content;
	if (*last_fd != -1)
		close(*last_fd);
	if (!head->next)
		close(pipe_fd[0]);
	if (cmd->output != NULL && cmd->output->fd >= 3)
		close(cmd->output->fd);
	if (cmd->input != NULL && cmd->input->fd >= 3)
		close(cmd->input->fd);
	close(pipe_fd[1]);
	*last_fd = pipe_fd[0];
}

void	wait_children(pid_t last_pid)
{
	pid_t			res;
	int				status;

	res = 0;
	signal(SIGINT, SIG_IGN);
	while (res != -1)
	{
		res = waitpid(-1, &status, 0);
		if (res == last_pid)
		{
			ft_setter(WEXITSTATUS(status));
			if (WIFSIGNALED(status))
				ft_setter(WTERMSIG(status) + 128);
		}
	}
	signal(SIGINT, sig_handler);
}

void	execution_multi_cmds(t_node *head, char **env)
{
	int			last_fd;
	int			pipe_fd[2];
	pid_t		*id;
	int			i;

	last_fd = -1;
	i = 0;
	id = (pid_t *) ft_calloc(ft_lstsize(head), sizeof(pid_t));
	while (head != NULL)
	{
		pipe(pipe_fd);
		id[i] = fork();
		if (id[i] == -1)
		{
			fork_failed(id, i);
			break ;
		}
		else if (id[i++] == 0)
			child_work(head, env, pipe_fd, last_fd);
		else
			parent_work(head, &last_fd, pipe_fd);
		head = head->next;
	}
	wait_children(id[i - 1]);
	free(id);
}
