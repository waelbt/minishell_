/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/08 19:03:00 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char *cwd_saver;


int is_directory(const char *path)
{
    struct stat path_stat;
	
	if(!ft_strchr((char *)path, '/'))
		return (0);
    stat(path, &path_stat);
    return (S_ISDIR(path_stat.st_mode));
}

void	error_handling(char *cmd, int flag)
{
	char *str;

	ft_setter(127);
	str = ": command not found\n";
	if (is_directory(cmd))
	{
		str = ": is a directory\n";
		ft_setter(126);
	}
	else if (errno == ENOENT)
	{
		if (ft_strchr(cmd, '/'))
			str = ": No such file or directory\n";
	}
	else if (errno == EACCES && ft_strchr(cmd , '/'))
		str = ": Permission denied\n";
	printf_error("minishell: ", cmd, str);
	if(flag == 0)
		exit(ft_getter());
}

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
		check_cmd(&cmd->after_expand[0], *env);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(cmd->after_expand[0], cmd->after_expand, *env);
		error_handling(cmd->after_expand[0], 0);
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
