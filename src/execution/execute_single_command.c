/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/07 18:46:28 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char *cwd_saver;

void	ft_execve(t_cmd *cmd, char ***env)
{
	int	id;
	int	status;

	id = fork();
	if (id == 0)
	{
		if (cmd->output != NULL)
			dup_norm(cmd->output->fd, 1);
		if (cmd->input != NULL)
			dup_norm(cmd->input->fd, 0);
		check_acces(&cmd->after_expand[0], *env);
		if (cmd->after_expand[0])
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execve(cmd->after_expand[0], cmd->after_expand, *env);
		}
		exit(127);
	}
	else
	{
		while (waitpid(id, &status, 0) != -1)
			;
		ft_setter(WEXITSTATUS(status));
		if (WIFSIGNALED(status))
			ft_setter(WTERMSIG(status) + 128);
	}
}

void	execution_cmd(t_node *head, char ***env)
{
	t_cmd		*cmd;
	char		*tmp;

	cmd = (t_cmd *)head->content;
	tmp = getcwd(NULL, 0);
	if(ft_strcmp(cmd->after_expand[0], "pwd") && tmp)
	{
		free(cwd_saver);
		cwd_saver = tmp;
	}
	if(cmd->e_rtype == VALID)
	{
		if (!(cmd->after_expand && cmd->after_expand[0]))
		{
			ft_setter(0);
			return ;
		}
		if (!execute(cmd->after_expand, env, 1))
			ft_execve(cmd, env);
	}
}
