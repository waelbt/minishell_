/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 15:15:17 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/13 22:55:14 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	dup_norm(int fildes1, int fildes2)
{
	dup2(fildes1, fildes2);
	close(fildes1);
}

void	fork_failed(int *i, int index, int last_fd)
{
	ft_setter(1);
	perror("minishell: fork");
	close(last_fd);
	while (--index != -1)
		kill(i[index], SIGKILL);
}

void	error_handling(char *cmd)
{
	char	*str;

	if (ft_strchr(cmd, '/'))
	{
		if (is_directory(cmd, 0))
		{
			str = ": is a directory\n";
			printf_error("minishell: ", cmd, str);
			exit(126);
		}
		else if (access(cmd, F_OK))
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

int	is_directory(char *path, int flag)
{
	struct stat	path_stat;

	if (!path)
		return (0);
	if (!ft_strchr(path, '/') && flag == 0)
		return (0);
	stat(path, &path_stat);
	return (S_ISDIR(path_stat.st_mode));
}
