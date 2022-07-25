/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:13:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/07/23 21:49:42 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	ft_close(t_node *head)
{
	t_redirec	*tmp;

	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		close(tmp->fd);
		head = head->next;
	}
}

char	*get_path(char **envp)
{
	int i;

	i = 0;
	while (envp && envp[i])
	{
		if ((ft_strncmp("PATH",  envp[i], 4)) == 0)
			return (&(envp[i][5]));
		i++;
	}
	return (NULL);
}

char	*invalid_command_error(char *cmd, char *path, char **paths)
{
	if (paths == NULL)
		printf_error("minishell: ", (cmd + 1), ": No such file or directory\n");
	else if (!ft_strcmp(cmd, "/"))
		printf_error("minishell: ", NULL, ": command not found\n");
	else if (path == NULL)
		printf_error("minishell: ", (cmd + 1), ": command not found\n");
	else
		return ((void *)1);
	free(cmd);
	return (NULL);
}
void check_acces(char **cmd, char **envp)
{
	if (access(*cmd, X_OK))
	{
		if (ft_strchr(*cmd, '/'))
		{
			printf_error("minishell: ", *cmd, ": command not found\n");
			free(*cmd);
			*cmd = NULL;
			return ;
		}
		*cmd = ft_strjoin("/", *cmd);
		*cmd = check_cmd(*cmd, envp);
	}
}
