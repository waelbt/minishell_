/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 12:57:29 by waboutzo          #+#    #+#             */
/*   Updated: 2022/08/13 22:56:12 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_oldpwd(char ***env, char *get_cwd, char *cwd_env)
{
	int		index;
	char	*str;
	char	*tmp;

	str = NULL;
	if (cwd_env)
		str = cwd_env;
	else if (get_cwd)
		str = get_cwd;
	index = get_index_of_double_char(*env, "OLDPWD");
	if (index != -1)
	{
		free((*env)[index]);
		(*env)[index] = ft_strdup("OLDPWD");
		if (str && !access(g_cwd_saver, X_OK))
		{
			tmp = (*env)[index];
			(*env)[index] = ft_strjoin((*env)[index], "=");
			free(tmp);
			tmp = (*env)[index];
			(*env)[index] = ft_strjoin((*env)[index], str);
			free(tmp);
		}
	}
}

void	update_pwd(char ***env, char *get_cwd, char *cwd_env)
{
	int		index;
	char	*str;

	index = get_index_of_double_char(*env, "PWD");
	if (index != -1)
	{
		free((*env)[index]);
		str = getcwd(NULL, 0);
		(*env)[index] = ft_strjoin("PWD=", str);
		free(str);
	}
	update_oldpwd(env, get_cwd, cwd_env);
}

static void	error_handler(char *path, char **ptr)
{
	if (!ft_strcmp(path, ""))
		return ;
	ft_setter(1);
	ptr[0] = ": No such file or directory\n";
	if (!path)
		ptr[0] = "cd: HOME not set\n";
	else if (!is_directory(path, 0))
			ptr[0] = ": Not a directory\n";
	else if (!access(path, F_OK) && access(path, R_OK))
		ptr[0] = ": Permission denied\n";
	printf_error("minishell: ", path, ptr[0]);
}

void	cd(char *path, char ***env)
{
	char	*ptr[3];

	ft_setter(0);
	if (!path)
	{
		path = dollar_value(*env, ft_strdup("HOME"));
		if (!ft_strcmp(path, "")
			&& get_index_of_double_char(*env, "HOME") == -1)
		{
			free(path);
			path = NULL;
		}
	}
	else
		path = ft_strdup(path);
	ptr[1] = getcwd(NULL, 0);
	ptr[2] = getpwd(*env);
	if (!(chdir(path) == -1))
		update_pwd(env, ptr[1], ptr[2]);
	else
		error_handler(path, ptr);
	free(ptr[2]);
	free(ptr[1]);
	free(path);
}
