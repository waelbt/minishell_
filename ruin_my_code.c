/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ruin_my_code.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 16:48:34 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/08 17:46:11 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "src/include/minishell.h"

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

char	*check_cmd(char *cmd, char **envp)
{
	char	**paths;
	char	*tmp[3];
	int		i;

	i = 0;
	tmp[2] = NULL;
	paths = ft_split(get_path(envp), ':');
	if (paths)
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
