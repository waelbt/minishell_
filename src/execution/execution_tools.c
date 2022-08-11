/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:13:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/11 03:15:37 by waboutzo         ###   ########.fr       */
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
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		if (!ft_strncmp("PATH", envp[i], 4))
			return (&(envp[i][5]));
		i++;
	}
	return (NULL);
}

void	procces_paths(char ***paths)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*paths)[i])
	{
		if (!ft_strcmp((*paths)[i], ""))
		{
			free((*paths)[i]);
			(*paths)[i] = ft_strdup("./");
		}
		else
		{
			tmp = (*paths)[i];
			(*paths)[i] = ft_strjoin(tmp, "/");
			free(tmp);
		}
		i++;
	}
}

char	*cmd_with_path(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = -1;
	paths = split_path(get_path(envp), ':');
	if (!paths)
		return (NULL);
	procces_paths(&paths);
	while (paths[++i])
	{
		tmp[0] = paths[i];
		paths[i] = ft_strjoin(tmp[0], cmd);
		free(tmp[0]);
		if (access(paths[i], X_OK) == 0)
			return (paths[i]);
		free(paths[i]);
	}
	free(paths);
	tmp[2] = ": command not found\n";
	printf_error("minishell: ", cmd, tmp[2]);
	exit(127);
	return (NULL);
}

char	*check_cmd(char *cmd, char **envp)
{
	char	*absolute_cmd;
	char	*tmp;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	absolute_cmd = cmd_with_path(cmd, envp);
	if (absolute_cmd)
		return (absolute_cmd);
	else
	{
		tmp = ft_strjoin("./", cmd);
		if (!access(tmp, F_OK) && !access(tmp, X_OK))
			return (tmp);
	}
	return (cmd);
}
