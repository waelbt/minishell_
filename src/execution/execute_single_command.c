/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 21:43:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/09 22:21:20 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char *cwd_saver;


int is_directory(char *path)
{
    struct stat path_stat;
	
	if (!path)
		return (0);
	if(!ft_strchr(path, '/'))
		return (0);
    stat(path, &path_stat);
    return (S_ISDIR(path_stat.st_mode));
}

void	error_handling(char *cmd)
{
	char *str;

 	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd))
		{
			str = ": is a directory\n";
			printf_error("minishell: ", cmd, str);
			exit(126);
		}
		else if (access(cmd , F_OK))
		{
			str = ": No such file or directory\n";
			printf_error("minishell: ", cmd, str);
			exit(127);
		}
	}
	if (!ft_strcmp(cmd, ""))
	{
		str = ": command not found\n";
		printf_error("minishell: ", cmd, str);
		exit(127);
	}
}

void	ft_execve(t_cmd *cmd, char ***env)
{
	int	id;
	int	status;
	char *path;

	id = fork();
	if (id == 0)
	{
		error_handling(cmd->after_expand[0]);
		path = check_cmd(cmd->after_expand[0], *env);
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->after_expand, *env);
		perror("minishell");
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
	int			t[2];
	
	cmd = (t_cmd *)head->content;
	if(cmd->e_rtype == VALID)
	{
		if (!(cmd->after_expand && cmd->after_expand[0]))
		{
			ft_setter(0);
			return ;
		}
		if(ft_strcmp(cmd->after_expand[0], "pwd"))
		{
			tmp =  getcwd(NULL, 0);
			if(tmp)
			{
				free(cwd_saver);
				cwd_saver = tmp;
			}
		}
		t[0] = dup(0);
		t[1] = dup(1);
		if (cmd->output != NULL)
			dup_norm(cmd->output->fd, 1);
		if (cmd->input != NULL)
			dup_norm(cmd->input->fd, 0);
		if (!execute(cmd->after_expand, env, 1))
			ft_execve(cmd, env);
		dup_norm(t[0], 0);
		dup_norm(t[1], 1);
	}
}
