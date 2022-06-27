/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 19:13:50 by waboutzo          #+#    #+#             */
/*   Updated: 2022/06/27 13:03:43 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

t_redirec	*ft_close(t_node *head)
{
	t_redirec	*redrec;
	t_redirec	*tmp;

	redrec = NULL;
	while (head != NULL)
	{
		tmp = (t_redirec *) head->content;
		close(tmp->fd);
		head = head->next;
	}
	return (redrec);
}

char	*get_path(char **envp)
{
	while (envp)
	{
		if ((ft_strncmp("PATH", *envp, 4)) == 0)
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*invalid_command_error(char *cmd, char *path)
{
	if (!ft_strcmp(cmd, "/"))
	{
		free(cmd);
		printf("minishell: : command not found\n");
	}
	else if (path == NULL)
	{
		printf("minishelll: %s: command not found\n", (cmd + 1));
		free(cmd);
	}
	else
		return ((void *)1);
	return (NULL);
}

char	*check_acces(char *cmd, char **envp)
{
	char	*tmp[2];

	if (access(cmd, X_OK))
	{
		if (ft_strchr(cmd, '/'))
			return (NULL);
		tmp[0] = ft_strdup("/");
		tmp[1] = cmd;
		cmd = ft_strjoin(tmp[0], tmp[1]);
		free(tmp[0]);
		free(tmp[1]);
		cmd = check_cmd(cmd, envp);
		if (!cmd)
			return (NULL);
	}
	return (cmd);
}