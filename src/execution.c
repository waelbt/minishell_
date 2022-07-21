/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:37:23 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/21 17:40:50 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = NULL;
	paths = ft_split(get_path(envp), ':');
	if(paths)
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
	t_redirec	*input;
	t_redirec	*output;
	char		**after_expand;

	cmd = (t_cmd *)head->content;
	after_expand = join_args(cmd->args);
	input = get_output_input(cmd->redrec, 1);
	output = get_output_input(cmd->redrec, 0);
	ft_setter(0);
	if (head->next != NULL)
		dup_norm(pipe_fd[1], 1);
	if (output != NULL)
		dup_norm(output->fd, 1);
	close(pipe_fd[0]);
	ft_close(cmd->redrec);
	if (after_expand && after_expand[0])
	{
		if(!execute(after_expand, &env))
		{
			if (last_fd != -1)
				dup_norm(last_fd, 0);
			if (input != NULL)
				dup_norm(input->fd, 0);
			check_acces(&after_expand[0], env);
			if(after_expand[0])
				execve(after_expand[0], after_expand, env);
		}
	}
	exit(127);
}

void	execution_multi_cmd(t_node *head, char **env)
{
	int		last_fd;
	int		pipe_fd[2];
	int		id;
	int		status;

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
	/*wach i9dr issali lpip tani 9bl men lkhr*/
	while (waitpid(-1, &status, 0) != -1)
		;
	ft_setter(WEXITSTATUS(status));
}

void	execution_single_command(t_node *head, char ***env)
{
	t_cmd		*cmd;
	t_redirec	*input;
	t_redirec	*output;
	int			id;
	char		**after_expand;
	int			fd_out;
	int			fd_int;
	int			status;

	cmd = (t_cmd *)head->content;
	after_expand = join_args(cmd->args);
	input = get_output_input(cmd->redrec, 1);
	output = get_output_input(cmd->redrec, 0);
	fd_out = dup(1);
	fd_int = dup(0);
	ft_setter(0);
	if (output != NULL)
		dup_norm(output->fd, 1);
	if (after_expand && after_expand[0])
	{
		if(!execute(after_expand, env))
		{
			id = fork();
			if(id == 0)
			{
				if (input != NULL)
					dup_norm(input->fd, 0);
				check_acces(&after_expand[0], *env);
				if(after_expand[0])
					execve(after_expand[0], after_expand, *env);
				//printf("ddd\n");
				exit(127);
			}
			else
			{
				waitpid(id , &status, 0);
				ft_setter(WEXITSTATUS(status));
				if (input != NULL)
					dup_norm(fd_int, 0);
				ft_close(cmd->redrec);
			}
		}
		free_double_char(after_expand, 0);
		if (output != NULL)
			dup_norm(fd_out, 1);
	}
}

void	execution(t_node *head, char ***env)
{
	// if (number_of_cmds(head) == 0)
	// 	return ((void *)1);
	if (ft_lstsize(head) == 1)
		execution_single_command(head, env);
	else
		execution_multi_cmd(head, *env);
}
