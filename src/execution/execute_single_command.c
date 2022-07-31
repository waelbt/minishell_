/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/30 09:05:06 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_execve(char **after_expand, char ***env)
{
	int id;
	int status;

	id = fork();
	if(id == 0)
	{
		check_acces(&after_expand[0], *env);
		if(after_expand[0])
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			execve(after_expand[0], after_expand, *env);
		}
		exit(127);
	}
	else
	{
		while(waitpid(id , &status, 0) != -1)
			;
		ft_setter(WEXITSTATUS(status));
		if(WIFSIGNALED(status))
			ft_setter(WTERMSIG(status) + 128);
	}
}

void		execution_cmd(t_node *head, char ***env)
{
	t_cmd		*cmd;
	int			fd[2];
	
	cmd = (t_cmd *)head->content;
	if (!(cmd->after_expand && cmd->after_expand[0]))
	{
		ft_setter(0);
		return ;
	}
	fd[1] = dup(1);
	fd[0] = dup(0);
	if (cmd->output != NULL)
		dup_norm(cmd->output->fd, 1);
	if (cmd->input != NULL)
		dup_norm(cmd->input->fd, 0);
	if(!execute(cmd->after_expand, env))
		ft_execve(cmd->after_expand, env);
	dup_norm(fd[1], 1);
	dup_norm(fd[0], 0);
}
