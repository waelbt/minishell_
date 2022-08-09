/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:13:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/09 14:23:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


char *cmd_with_path(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = -1;
	paths = split_path(get_path(envp), ':');
	if (!paths)
		return (NULL);
	while (paths[++i])
	{
		if(ft_strcmp(paths[i], ""))
		{
			tmp[0] = paths[i];
			paths[i] = ft_strjoin(paths[i], "/");
			free(tmp[0]);
		}
		tmp[0] = paths[i];
		paths[i] = ft_strjoin(tmp[0], cmd);
		if (access(paths[i], X_OK) == 0)
		{
			if (!ft_strcmp(tmp[0], ""))
				return (tmp[0]);
			free(tmp[0]);
			return (paths[i]);
		}
		free(paths[i]);
		free(tmp[0]);
	}
	free(paths);
	return (NULL);
}

char *check_cmd(char *cmd, char **envp)
{
	char	*absolute_cmd;

	absolute_cmd = NULL;
	if (!ft_strchr(cmd, '/'))
		absolute_cmd = cmd_with_path(cmd, envp);
	if (absolute_cmd && ft_strcmp(cmd, "") && ft_strcmp(cmd, "/"))
		return (absolute_cmd);
	return (cmd);
}
