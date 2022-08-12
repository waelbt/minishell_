/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/12 15:07:49 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_execve(t_cmd *cmd, char ***env)
{
	int		var[2];
	char	*path;

	var[0] = fork();
	if (var[0] == -1)
	{
		ft_setter(1);
		perror("minishell: fork");
		return ;
	}
	else if (var[0] == 0)
	{
		error_handling(cmd->after_expand[0]);
		path = check_cmd(cmd->after_expand[0], *env);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->after_expand, *env);
		perror("minishell");
		exit(127);
	}
	waitpid(var[0], &var[1], 0);
	ft_setter(WEXITSTATUS(var[1]));
	if (WIFSIGNALED(var[1]))
		ft_setter(WTERMSIG(var[1]) + 128);
}

void	save_pwd(char *s)
{
	char	*tmp;

	tmp = getcwd(NULL, 0);
	if (tmp)
	{
		if (ft_strcmp(s, "pwd"))
		{
			free(g_cwd_saver);
			g_cwd_saver = tmp;
		}
		else
			free(tmp);
	}
}

void	execution_cmd(t_node *head, char ***env)
{
	t_cmd		*cmd;
	int			save_std[2];

	cmd = (t_cmd *)head->content;
	if (cmd->e_rtype == VALID)
	{
		if (!(cmd->after_expand && cmd->after_expand[0]))
		{
			ft_setter(0);
			return ;
		}
		save_pwd(cmd->after_expand[0]);
		save_std[0] = dup(0);
		save_std[1] = dup(1);
		if (cmd->output != NULL)
			dup_norm(cmd->output->fd, 1);
		if (cmd->input != NULL)
			dup_norm(cmd->input->fd, 0);
		if (!execute(cmd->after_expand, env, 1))
			ft_execve(cmd, env);
		dup_norm(save_std[0], 0);
		dup_norm(save_std[1], 1);
	}
}
